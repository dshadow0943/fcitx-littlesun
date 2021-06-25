/***************************************************************************
 *   Copyright (C) 2010~2011 by CSSlayer                                   *
 *   wengxt@gmail.com                                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#include <memory>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcitx/ime.h>
#include <fcitx-config/hotkey.h>
#include <fcitx-config/xdg.h>
#include <fcitx-utils/log.h>
#include <fcitx-config/fcitx-config.h>
#include <fcitx-utils/utils.h>
#include <fcitx/instance.h>
#include <fcitx/keys.h>
#include <fcitx/module.h>
#include <fcitx/context.h>
#include <fcitx/module/punc/fcitx-punc.h>
#include <string>
#include <libintl.h>

#include "config.h"
#include "eim.h"
#include "bus.h"
#include "common.h"

extern "C" {
    FCITX_DEFINE_PLUGIN(fcitx_littlesun, ime2, FcitxIMClass2) = {
        FcitxLittleSunCreate,
        FcitxLittleSunDestroy,
        FcitxLittleSunReloadConfig,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
}


//CONFIG_DEFINE_LOAD_AND_SAVE(FcitxLibPinyinConfig, FcitxLittleSunConfig, "fcitx-libpinyin")

static void FcitxLittleSunSave(void* arg);


/**
 * @brief Reset the status.
 *
 **/
void FcitxLittleSunReset(void* arg)
{
    FcitxLittleSun* libpinyin = (FcitxLittleSun*) arg;
    libpinyin->reset();
}


/**
 * @brief Process Key Input and return the status
 *
 * @param keycode keycode from XKeyEvent
 * @param state state from XKeyEvent
 * @param count count from XKeyEvent
 * @return INPUT_RETURN_VALUE
 **/
INPUT_RETURN_VALUE FcitxLittleSunDoInput(void* arg, FcitxKeySym sym, unsigned int state)
{
    return IRV_TO_PROCESS;
}

boolean FcitxLittleSunInit(void* arg)
{
    FcitxLittleSun* libpinyin = (FcitxLittleSun*) arg;
    libpinyin->init();
    return true;
}

void FcitxLittleSun::init() {
    FcitxInstanceSetContext(m_owner->owner, CONTEXT_IM_KEYBOARD_LAYOUT, "us");
    m_owner->k_bus->initView();

}

void FcitxLittleSun::reset() {
    m_owner->k_bus->showView();

}

void FcitxLittleSun::save() {
    m_owner->k_bus->hideView();

}


FcitxLittleSun::FcitxLittleSun(FcitxLittleSunAddonInstance* littlesunaddon) :
    m_owner(littlesunaddon)
{
}

FcitxLittleSun::~FcitxLittleSun()
{

}

/**
 * @brief initialize the extra input method
 *
 * @param arg
 * @return successful or not
 **/
void* FcitxLittleSunCreate(FcitxInstance* instance)
{
    FcitxLittleSunAddonInstance* littlesunaddon = (FcitxLittleSunAddonInstance*) fcitx_utils_malloc0(sizeof(FcitxLittleSunAddonInstance));
    littlesunaddon->owner = instance;

    littlesunaddon->pinyin = new FcitxLittleSun(littlesunaddon);

    FcitxInstanceRegisterIM(instance,
                            littlesunaddon->pinyin,
                            "keyboard-littlesun",
                            "小太阳键盘",
                            "littlesun",
                            FcitxLittleSunInit,
                            FcitxLittleSunReset,
                            FcitxLittleSunDoInput,
                            NULL,
                            NULL,
                            FcitxLittleSunSave,
                            NULL,
                            NULL,
                            5,
                            "zh_CN"
                           );

    littlesunaddon->bus = new FcitxLittleSunBus(littlesunaddon);
    littlesunaddon->k_bus = new KeyboardBus(littlesunaddon);

    return littlesunaddon;
}

/**
 * @brief Destroy the input method while unload it.
 *
 * @return int
 **/
void FcitxLittleSunDestroy(void* arg)
{
    FcitxLittleSunAddonInstance* libpinyin = (FcitxLittleSunAddonInstance*) arg;
    libpinyin->k_bus->hideView();
    delete libpinyin->pinyin;
    delete libpinyin->bus;
    delete libpinyin->k_bus;
    free(libpinyin);
}

void FcitxLittleSunReloadConfig(void* arg)
{

}

void FcitxLittleSunSave(void* arg)
{
    FcitxLittleSun* liblittlesun = (FcitxLittleSun*) arg;
    liblittlesun->save();
}

