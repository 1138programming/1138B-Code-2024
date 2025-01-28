#pragma once

#include "liblvgl/lvgl.h"
#include <stdio.h>
#include <vector>
#include <stdbool.h>
#include <stdlib.h>
#include "pros/motor_group.hpp"
#include "pros/motors.hpp"
#include "pros/colors.hpp"

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

typedef struct {
    void (*function)(void);   // Function pointer
    const char* name;         // Function name
} func_item_t;

// Struct for list item data
typedef struct {
    func_item_t item;
    lv_obj_t* list_item;
} list_item_data_t;

struct motor_item_t {
    const char* motorName;
    int motorPort;

     // Constructor for single motors
    motor_item_t(const char* name, int port)
        : motorName(name), motorPort(port) {}
};

// Declare the HomePage class
class Screen {
public:
    // Constructor
    Screen(std::vector<func_item_t> blue_functions_, std::vector<func_item_t> red_functions_, std::vector<motor_item_t> motors_);

    enum Pages {
        HOME,
        MOTOR,
        DATA,
        LOGO
    };

    // Public method to initialize the page
    void init(int logLines);
    // Public methods for handling UI interactions
    void runSelected();
    void print(int line, const char* fmt, ...);         // Print to a specific line
    void updateMotorData();
    void addMotor(const motor_item_t& motor);
    pros::Color getSelectedColor();
    void addBlueFunction(const func_item_t& func);
    void addRedFunction(const func_item_t& func);
    void setPage(Pages newPage);

private:
    // Private member variables
    void homePage();
    void motorPage();
    void logPage(int num_lines); // Create the log page
    void logoPage();
    void setDarkModeStyle();
    void updateList();
    std::vector<lv_obj_t*> motor_buttons;
    std::vector<lv_obj_t*> motor_labels;
    std::vector<func_item_t> blue_functions; // List for blue functions
    std::vector<func_item_t> red_functions;  // List for red functions
    std::vector<motor_item_t> motors;
    static void toggleButtonEventHandler(lv_event_t* e);
    static void listItemEventHandler(lv_event_t* e);
    static void motorButtonEventHandler(lv_event_t* e);
    static void backButtonEventHandler(lv_event_t* e);
    static void dataButtonEventHandler(lv_event_t* e);
    lv_obj_t* list;
    bool is_blue;
    list_item_data_t* selected_item_data;
    lv_obj_t* logScreen; // Log page object
    lv_obj_t* homeScreen;
    lv_obj_t* motorScreen;
    lv_obj_t* logoScreen;
    std::vector<lv_obj_t*> log_labels; // Vector of labels for each line

};
