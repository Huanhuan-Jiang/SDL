#include <SDL3/SDL.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <memory>

// Custom log output function
void CustomLogOutput(void *userdata, int category, SDL_LogPriority priority, const char *message) {
    std::ofstream *file = static_cast<std::ofstream *>(userdata);

    if (file && file->is_open()) {
        *file << "[SDL_GetLogPriority]: " << message << "\n";
        if (file->fail()) {
            std::cerr << "Error writing to file!" << std::endl;
        }
    } else {
        std::cerr << "File stream is not open or invalid!" << std::endl;
    }

    *file << "[SDL_GetLogPriority]: " << message << "\n";
}

int main(int argc, char* argv[]) {
    // Open a log file for writing
    std::unique_ptr<std::ofstream> log_file_ptr(new std::ofstream("sdl_log.txt"));

    log_file_ptr = std::make_unique<std::ofstream>("sdl_log.txt");

    if (!log_file_ptr->is_open()) {
        std::cerr << "Failed to open log file!" << std::endl;
        return 1;
    }

    SDL_LogWarn(SDL_LOG_CATEGORY_VIDEO, "try SDL_LogWarn before SDL_SetLogOutputFunction");

    // Redirect SDL log messages to the custom output function
    SDL_SetLogOutputFunction(reinterpret_cast<SDL_LogOutputFunction>(CustomLogOutput), log_file_ptr.get());
    
    SDL_Window *window;                    // Declare a pointer

    SDL_Init(SDL_INIT_VIDEO);              // Initialize SDL

    // Create an application window with the following settings:
    window = SDL_CreateWindow(
        "An SDL3 window",                  // window title
        640,                               // width, in pixels
        480,                               // height, in pixels
        SDL_WINDOW_OPENGL                  // flags - see below
    );

    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        //SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    // The window is open: could enter program loop here (see SDL_PollEvent())

    SDL_Delay(3000);  // Pause execution for 3000 milliseconds, for example

    // Close and destroy the window
    SDL_DestroyWindow(window);

    // Clean up
    //SDL_Quit();
    return 0;
}
