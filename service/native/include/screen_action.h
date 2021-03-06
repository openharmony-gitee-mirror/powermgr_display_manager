/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef DISPLAYMGR_SCREEN_ACTION_H
#define DISPLAYMGR_SCREEN_ACTION_H

#include <functional>
#include <memory>
#include <vector>

#include <display_device.h>

#include "display_info.h"

namespace OHOS {
namespace DisplayPowerMgr {
class ScreenAction {
public:
    ScreenAction();
    ~ScreenAction() = default;
    std::vector<uint32_t> GetDisplayIds();
    DisplayState GetPowerState(uint32_t devId);
    bool SetPowerState(uint32_t devId, DisplayState state);
    uint32_t GetBrightness(uint32_t devId);
    bool SetBrightness(uint32_t devId, uint32_t value);

private:
    struct DeviceFuncCloser {
        void operator()(DeviceFuncs* f)
        {
            (void)DeviceUninitialize(f);
        }
    };
    using DeviceFuncPtr = std::unique_ptr<DeviceFuncs, DeviceFuncCloser>;

    static inline int32_t GetValidBrightness(int32_t value)
    {
        return (value < MIN_BRIGHTNESS) ? MIN_BRIGHTNESS : ((value > MAX_BRIGHTNESS) ? MAX_BRIGHTNESS : value);
    }

    static constexpr int32_t MAX_BRIGHTNESS = 255;
    static constexpr int32_t MIN_BRIGHTNESS = 6;

    std::vector<uint32_t> devIds_;
    DeviceFuncPtr hdiFuncs_;
};
} // namespace DisplayPowerMgr
} // namespace OHOS
#endif // DISPLAYMGR_SCREEN_ACTION_H
