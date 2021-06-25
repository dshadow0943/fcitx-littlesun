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

#ifndef EIM_H
#define EIM_H

#include <fcitx/ime.h>
#include <fcitx-config/fcitx-config.h>
#include <fcitx/instance.h>
#include <fcitx/candidate.h>
#include <vector>
#include <string>
#include "bus.h"
#include "common.h"
#include "keyboardbus.h"


struct FcitxLittleSunConfig
{
    FcitxGenericConfig gconfig;
};


CONFIG_BINDING_DECLARE(FcitxLittleSunConfig);
void* FcitxLittleSunCreate(FcitxInstance* instance);
void FcitxLittleSunDestroy(void* arg);
INPUT_RETURN_VALUE FcitxLittleSunDoInput(void* arg, FcitxKeySym sym, unsigned int state);
boolean FcitxLittleSunInit(void*);
void FcitxLittleSunReloadConfig(void*);

class FcitxLittleSun;

typedef struct _FcitxLittleSunAddonInstance {
    FcitxLittleSunConfig config;

    FcitxLittleSun* pinyin;
    FcitxInstance* owner;
    KeyboardBus* k_bus;
    FcitxLittleSunBus* bus;
} FcitxLittleSunAddonInstance;

class FcitxLittleSun
{
public:
    FcitxLittleSun(FcitxLittleSunAddonInstance* libpinyinaddon);
    ~FcitxLittleSun();

    void reset();
    void init();
    void destroy();
    void save();

private:
    FcitxLittleSunAddonInstance* m_owner;
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 0;
