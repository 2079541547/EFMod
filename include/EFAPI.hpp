/*******************************************************************************
 * 文件名称: EFAPI
 * 项目名称: EFMod
 * 创建时间: 2024/12/1
 * 作者: EternalFuture゙
 * Github: https://github.com/2079541547
 * 版权声明: Copyright © 2024 EternalFuture. All rights reserved.
 * 许可证: Licensed under the Apache License, Version 2.0 (the "License");
 *         you may not use this file except in compliance with the License.
 *         You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0
 *
 *         Unless required by applicable law or agreed to in writing, software
 *         distributed under the License is distributed on an "AS IS" BASIS,
 *         WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *         See the License for the specific language governing permissions and
 *         limitations under the License.
 *
 * 描述信息: 本文件为EFMod项目中的一部分，允许在遵守Apache License 2.0的条件下自由用于商业用途。
 * 注意事项: 请严格遵守Apache License 2.0协议使用本代码。Apache License 2.0允许商业用途，无需额外授权。
 *******************************************************************************/

#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <error.h>
#include "SilkHash64.hpp"


/// @brief 全局指针，指向存储字段映射的 map。
/// 键为 uint64_t 类型的哈希值，值为 void* 指针，指向具体的字段数据。
std::map<uint64_t, void*>* FieldMap;

/// @brief 全局指针，指向存储函数映射的 map。
/// 键为 uint64_t 类型的哈希值，值为 void* 指针，指向具体的函数。
std::map<uint64_t, void*>* FuncMap;

namespace EFMod::API {
    /**
     * @brief 结构体 EFModAPI_Func 用于唯一标识一个函数。
     *
     * 包含了命名空间、类名、函数名、返回类型描述符以及参数个数等信息，
     * 以便在运行时动态查找并调用对应的函数。
     */
    struct EFModAPI_Func {
        std::string Namespace; ///< 函数所在的命名空间
        std::string Class;     ///< 函数所属的类名
        std::string Name;      ///< 函数名称
        std::string Return;    ///< 函数返回类型的描述符
        int arg;               ///< 参数个数或特定参数值，用于区分重载函数

        /**
         * @brief 创建唯一的键字符串，用于生成哈希值。
         * @return 返回由命名空间、类名、函数名、参数个数及返回类型组成的字符串。
         */
        std::string getKey() const {
            return Namespace + Class + Name + std::to_string(arg) + Return;
        }
    };

    /**
     * @brief 结构体 EFModAPI_Field 用于唯一标识一个字段。
     *
     * 包含了命名空间、类名和字段名信息，以便在运行时动态获取对应的字段值。
     */
    struct EFModAPI_Field {
        std::string Namespace; ///< 字段所在的命名空间
        std::string Class;     ///< 字段所属的类名
        std::string Name;      ///< 字段名称

        /**
         * @brief 创建唯一的键字符串，用于生成哈希值。
         * @return 返回由命名空间、类名和字段名组成的字符串。
         */
        std::string getKey() const {
            return Namespace + Class + Name;
        }
    };

    /**
     * @brief 模板函数 GetField 用于从 FieldMap 中获取并转换指定类型的字段。
     *
     * @tparam R 返回值类型，模板参数决定了返回的具体数据类型。
     * @param FIELD 字段标识符，包含命名空间、类名和字段名信息。
     * @return 返回目标字段的值，其类型由模板参数 R 决定。
     *
     * @throws std::out_of_range 如果提供的键不在 FieldMap 中。
     * @throws std::bad_cast 理论上不会发生，但为了完整性添加此异常说明。
     */
    template <typename R>
     R GetField(const EFModAPI_Field& FIELD) {
        // 生成唯一的键，并查找 FieldMap 中是否存在该键。
        auto key = SilkHash64::hashString(FIELD.getKey());
        auto it = FieldMap->find(key);

        if (it == FieldMap->end()) {
            throw std::out_of_range("Field not found in FieldMap");
        }

        // 将 void** 转换为指向 R 类型的指针，并解引用以获取实际的字段值。
        // 注意：这里假设 FieldMap 中存储的指针确实是指向 R 类型的数据。
        // 如果这个假设不成立，行为将是未定义的。
        return **reinterpret_cast<R**>(it->second);
    }

    /**
     * @brief 模板函数 callFunction 用于从 FuncMap 中获取并调用指定类型的函数。
     *
     * @tparam R 返回值类型，模板参数决定了函数的返回类型。
     * @tparam Args 参数包，表示可变数量和类型的参数。
     * @param FUNC 函数标识符，包含命名空间、类名、函数名、参数个数及返回类型信息。
     * @param args 可变数量和类型的参数，这些参数将被转发给目标函数。
     * @return 返回目标函数的执行结果，其类型由模板参数 R 决定。
     *
     * @throws std::out_of_range 如果提供的键不在 FuncMap 中。
     * @throws std::bad_cast 如果转换失败（理论上不会发生，但为了完整性添加）。
     */
    template <typename R, typename... Args>
    R callFunction(EFModAPI_Func FUNC, Args&&... args) {
        // 生成唯一的键，并查找 FuncMap 中是否存在该键。
        auto key = SilkHash64::hashString(FUNC.getKey());
        auto it = FuncMap->find(key);

        if (it == FuncMap->end()) {
            throw std::out_of_range("Function not found in FuncMap");
        }

        // 定义函数指针类型，指向接受 Args... 类型参数并返回 R 类型的函数。
        using FuncPtr = R (*)(Args...);

        // 将 void* 转换为正确的函数指针类型，并调用目标函数。
        // 注意：这里假设 FuncMap 中存储的指针确实是指向正确类型的函数。
        // 如果这个假设不成立，行为将是未定义的。
        auto f = reinterpret_cast<FuncPtr>(it->second);
        return f(std::forward<Args>(args)...);
    }
}