/*******************************************************************************
 * 文件名称: EFMod
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
#include <vector>
#include "EFAPI.hpp"
#include "CoreAPI.hpp"

namespace EFMod {

    /**
     * @brief 结构体 HOOKS 用于Hook一个指定函数。
     *
     * 包含了命名空间、类名、函数名、返回类型描述符以及参数个数等信息，
     * 以便在运行时动态查找并hook对应的函数。
     */
    struct HOOKS {
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

    // HOOKS 应该是一个枚举类型或者有 getKey 方法的类/结构体，用于标识不同的钩子类型。
    // 由于没有给出 HOOKS 的具体定义，我们假设它是一个具有 getKey() 成员函数的类或结构体，
    // 返回一个可以被 SilkHash64::hashString 接受的字符串键。
    // 全局变量 hooks 用来存储不同类型的钩子及其对应的函数指针列表。
    // 使用 uint64_t 作为键，以确保即使在32位系统上也能有足够的范围来避免哈希冲突。
    // 使用 void* 来存储指针。
    inline std::map<uint64_t, std::vector<void *>> hooks;

    /**
     * @brief 初始化函数，可能用于初始化与注册钩子有关的资源。
     *
     * 这个函数应该在应用程序的启动阶段调用一次，以确保所有需要的资源都已准备好。
     *
     * @return true 如果初始化成功。
     * @return false 如果初始化失败。
     */
    bool initialization();

    /**
     * @brief 注册一个新的钩子到全局 hooks 映射中。
     *
     * 此函数将给定的 Hook 对象（通过其字符串键）和指向函数的指针 PTR 注册到全局 hooks 映射中。
     * Hook 的字符串键会通过 SilkHash64::hashString 函数转换为一个哈希值，作为 map 的键。
     * 函数指针 PTR 的地址会被转换为 uintptr_t 类型，并添加到对应哈希值的 vector 中。
     *
     * 注意：这里使用了 &PTR，这实际上获取的是指针变量本身的地址，而不是指针所指向的地址。
     *      如果意图是保存函数指针本身，那么不应该取地址(&)操作符。
     *
     * @param Hook 钩子对象，必须实现 getKey() 方法返回唯一字符串键。
     * @param PTR 指向要挂钩的函数的指针。
     */
    void registerHook(HOOKS Hook, void* PTR) {
        // 将 Hook 的字符串键转换为哈希值，并将其作为键添加到 hooks map 中。
        // 然后将函数指针 PTR 的地址添加到对应的 vector 中。
        hooks[SilkHash64::hashString(Hook.getKey())].push_back(PTR);
    }
}

/**
 * @function get_hooks
 * @brief 获取当前模组的所有钩子。
 *
 * 此函数返回一个映射表，其中键是64位无符号整数，代表钩子的唯一标识符；
 * 值是一个void*指针的向量，表示与该标识符关联的一系列钩子函数指针。
 * 这个函数通常由模组加载器调用，以获取模组提供的所有钩子，并将其集成到全局钩子管理系统中。
 *
 * @return std::map<uint64_t, std::vector<void *>> 钩子映射表。
 */
extern "C" std::map<uint64_t, std::vector<void *>> get_hooks();

/**
 * @function CreateMod
 * @brief 初始化模组。
 *
 * 此函数负责执行模组的初始化逻辑。它应该在模组加载时被调用，以确保所有必要的资源和状态都被正确设置。
 * 模组加载器通常会在加载完模组后立即调用这个函数，以开始模组的生命周期。
 */
extern "C" void CreateMod();