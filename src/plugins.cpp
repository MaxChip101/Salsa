#include <iostream>
#include <filesystem>
#include <vector>
#include <dlfcn.h>
#include <ncurses.h>
#include <string>
#include "display.h"
#include "plugins.h"

Context* getContext(void)
{
    return new Context();
}

void destroyContext(Context* context)
{
    delete context;
}


struct Loaded_Plugin {
    Salsa_Plugin* plugin;
    void* handle;
};

std::vector<Loaded_Plugin> loaded_plugins;

void load_plugins(const std::string& plugin_dir) {

    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(plugin_dir)) {

        if (entry.is_regular_file() && entry.path().extension() == ".so") {

            const std::string plugin_path = entry.path().string();

            // Load the plugin
            void* handle = dlopen(plugin_path.c_str(), RTLD_LAZY);
            if (!handle) {
                std::cerr << "Failed to load " << plugin_path << ": " << dlerror() << std::endl;
                continue;
            }

            dlerror(); // Clear any existing errors

            // Load the plugin symbol
            Salsa_Plugin* plugin = (Salsa_Plugin*)dlsym(handle, "plugin");
            char* error = dlerror();
            if (error) {
                std::cerr << "Failed to load symbol 'plugin' in " << plugin_path << ": " << error << std::endl;
                dlclose(handle);
                continue;
            }

            // Store the plugin and its handle
            loaded_plugins.push_back({plugin, handle});

            // Initialize the plugin
            plugin->init();
            std::cout << "Loaded plugin: " << plugin->name << std::endl;
        }
    }
}

void plugin_update() {
    for (const Loaded_Plugin& entry : loaded_plugins)
    {
        entry.plugin->update();
    }
}

void end_plugins() {
    for (const Loaded_Plugin& entry : loaded_plugins)
    {
        entry.plugin->end();
        dlclose(entry.handle);
    }
    loaded_plugins.clear();
}

void send_key(const char* text)
{
    printw(text);
    for (const Loaded_Plugin& entry : loaded_plugins)
    {
        entry.plugin->input(text);
    }
}