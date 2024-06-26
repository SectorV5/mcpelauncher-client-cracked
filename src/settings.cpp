#include "settings.h"
#include <properties/property_list.h>
#include <properties/property.h>
#include <mcpelauncher/path_helper.h>
#include <fstream>

std::optional<bool> Settings::enable_imgui = {};
int Settings::menubarsize = 0;
std::string Settings::clipboard;
bool Settings::enable_keyboard_autofocus_patches_1_20_60 = false;
bool Settings::enable_keyboard_tab_patches_1_20_60 = false;
bool Settings::enable_menubar = true;
int Settings::fps_hud_location;
int Settings::keystroke_mouse_hud_location;
std::string Settings::videoMode;

static properties::property_list settings('=');
static properties::property<std::string> enable_imgui(settings, "enable_imgui", "auto");
static properties::property<bool> enable_keyboard_autofocus_patches_1_20_60(settings, "enable_keyboard_autofocus_patches_1_20_60", /* default if not defined*/ false);
static properties::property<bool> enable_keyboard_tab_patches_1_20_60(settings, "enable_keyboard_tab_patches_1_20_60", /* default if not defined*/ false);
static properties::property<bool> enable_menubar(settings, "enable_menubar", /* default if not defined*/ true);
static properties::property<int> fps_hud_location(settings, "fps_hud_location", /* default if not defined*/ -1);
static properties::property<int> keystroke_mouse_hud_location(settings, "keystroke_mouse_hud_location", /* default if not defined*/ -1);
static properties::property<std::string> videoMode(settings, "videoMode", "");

std::string Settings::getPath() {
    return PathHelper::getPrimaryDataDirectory() + "mcpelauncher-client-settings.txt";
}

void Settings::load() {
    std::ifstream propertiesFile(getPath());
    if (propertiesFile) {
        settings.load(propertiesFile);
    }
    if(::enable_imgui.get() != "auto") {
        properties::property_list dummy;
        properties::property<bool> dummy_enable_imgui(dummy, "enable_imgui", false);
        dummy_enable_imgui.parse_value(::enable_imgui.get());
        Settings::enable_imgui = dummy_enable_imgui.get();
    }
    Settings::enable_keyboard_autofocus_patches_1_20_60 = ::enable_keyboard_autofocus_patches_1_20_60.get();
    Settings::enable_keyboard_tab_patches_1_20_60 = ::enable_keyboard_tab_patches_1_20_60.get();
    Settings::enable_menubar = ::enable_menubar.get();
    Settings::fps_hud_location = ::fps_hud_location.get();
    Settings::keystroke_mouse_hud_location = ::keystroke_mouse_hud_location.get();
    Settings::videoMode = ::videoMode.get();
}

void Settings::save() {
    if(Settings::enable_imgui.has_value()) {
        ::enable_imgui.set(Settings::enable_imgui.value() ? "true" : "false");
    } else {
        ::enable_imgui.set("auto");
    }
    ::enable_keyboard_autofocus_patches_1_20_60.set(Settings::enable_keyboard_autofocus_patches_1_20_60);
    ::enable_keyboard_tab_patches_1_20_60.set(Settings::enable_keyboard_tab_patches_1_20_60);
    ::enable_menubar.set(Settings::enable_menubar);
    ::fps_hud_location.set(Settings::fps_hud_location);
    ::keystroke_mouse_hud_location.set(Settings::keystroke_mouse_hud_location);
    ::videoMode.set(Settings::videoMode);
    std::ofstream propertiesFile(getPath());
    if (propertiesFile) {
        settings.save(propertiesFile);
    }
}
