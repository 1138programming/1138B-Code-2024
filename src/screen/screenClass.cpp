#include "liblvgl/lvgl.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "screen/screenClass.hpp"
#include "screen/logo.h"
#include "systems/intake.hpp"


// Define button styles
lv_style_t btn_style;
lv_style_t btn_checked_style;
lv_style_t list_style;
lv_style_t screen_btn_style;

struct EventData {
    Screen* screen;
    list_item_data_t* item_data;
};

// Function to determine the color based on temperature and power level
lv_color_t getMotorColor(double temperature) {
    // Define colors for each level
    //lv_color_t level0_color = lv_color_hex(0x73EA6E); // Green
    //lv_color_t level1_color = lv_color_hex(0xF3F677); // Yellow
    //lv_color_t level2_color = lv_color_hex(0xF6B877); // Orange
    //lv_color_t level3_color = lv_color_hex(0xF67E77); // Light Red
    //lv_color_t level4_color = lv_color_hex(0xF377F6); // Dark Red
    lv_color_t level0_color = lv_color_hex(0xE0E0E0); // off white
    lv_color_t level1_color = lv_color_hex(0xA19FA1); // light grey
    lv_color_t level2_color = lv_color_hex(0x5B5A5B); // dark grey
    lv_color_t level3_color = lv_color_hex(0x252525); // basically black

    // Determine the level and corresponding color
    if (temperature < 55.0) {
        return level0_color;  // Level 0: Safe (Green)
    }
    else if (temperature < 60.0) {
        return level1_color;  // Level 1: Moderate warning (Yellow)
    }
    else if (temperature < 65.0) {
        return level2_color;  // Level 2: Increased warning (Orange)
    }
    else {
        return level3_color;  // Level 3: Critical (Light Red)
    }
}

// Function to determine the color based on temperature and power level
lv_color_t getMotorLabelColor(double temperature) {
    // Define colors for each level
    //lv_color_t level0_color = lv_color_hex(0x73EA6E); // Green
    //lv_color_t level1_color = lv_color_hex(0xF3F677); // Yellow
    //lv_color_t level2_color = lv_color_hex(0xF6B877); // Orange
    //lv_color_t level3_color = lv_color_hex(0xF67E77); // Light Red
    //lv_color_t level4_color = lv_color_hex(0xF377F6); // Dark Red
    lv_color_t level0_color = lv_color_black(); // Green
    lv_color_t level1_color = lv_color_black(); // Yellow
    lv_color_t level2_color = lv_color_white(); // Orange
    lv_color_t level3_color = lv_color_white(); // Light Red

    // Determine the level and corresponding color
    if (temperature < 55.0) {
        return level0_color;  // Level 0: Safe (Green)
    }
    else if (temperature < 60.0) {
        return level1_color;  // Level 1: Moderate warning (Yellow)
    }
    else if (temperature < 65.0) {
        return level2_color;  // Level 2: Increased warning (Orange)
    }
    else {
        return level3_color;  // Level 3: Critical (Light Red)
    }
}


// Class definition for the HomePag

// Constructor for the HomePage class
Screen::Screen(std::vector<func_item_t> blue_functions_, std::vector<func_item_t> red_functions_, std::vector<motor_item_t> motors_) {
    blue_functions = blue_functions_;
    red_functions = red_functions_;
    motors = motors_;
    is_blue = true;
    selected_item_data = NULL;
}

// Initialize the UI components and apply dark mode style
void Screen::init(int logLines) {
    setDarkModeStyle();
    homePage();
    motorPage();
    logPage(logLines);
    logoPage();
}

void Screen::homePage() {
    homeScreen = lv_obj_create(NULL);
    lv_obj_add_style(homeScreen, &btn_style, LV_STATE_DEFAULT);
    // Create list and add styles
    list = lv_list_create(homeScreen);
    lv_obj_add_style(list, &list_style, 0);
    lv_obj_set_size(list, lv_pct(75), lv_pct(100));
    lv_obj_align(list, LV_ALIGN_LEFT_MID, 0, 0);

    // Create toggle button
    lv_obj_t* toggle_btn = lv_btn_create(homeScreen);
    lv_obj_set_size(toggle_btn, lv_pct(25), lv_pct(100 / 3));
    lv_obj_align(toggle_btn, LV_ALIGN_TOP_RIGHT, 0, 1);
    lv_obj_set_style_transform_width(toggle_btn, 0, LV_STATE_PRESSED);
    lv_obj_set_style_transform_height(toggle_btn, 0, LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(toggle_btn, 0, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(toggle_btn, 0, LV_STATE_DEFAULT);

    lv_obj_t* btn_label = lv_label_create(toggle_btn);
    lv_label_set_text(btn_label, "Blue");
    lv_obj_center(btn_label);

    lv_obj_add_event_cb(toggle_btn, toggleButtonEventHandler, LV_EVENT_CLICKED, this);

    updateList();

    // Create Motor button
    lv_obj_t* motor_btn = lv_btn_create(homeScreen);
    lv_obj_set_size(motor_btn, lv_pct(25), lv_pct(100 / 3));
    lv_obj_align(motor_btn, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_style(motor_btn, &screen_btn_style, LV_STATE_DEFAULT);
    lv_obj_set_style_transform_width(motor_btn, 0, LV_STATE_PRESSED);
    lv_obj_set_style_transform_height(motor_btn, 0, LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(motor_btn, 0, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(motor_btn, 0, LV_STATE_DEFAULT);

    lv_obj_t* motor_label = lv_label_create(motor_btn);
    lv_label_set_text(motor_label, "Motor\nTemperatures");
    lv_obj_set_style_text_align(motor_label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
    lv_obj_center(motor_label);
    lv_obj_add_style(motor_label, &screen_btn_style, LV_STATE_DEFAULT);

    lv_obj_add_event_cb(motor_btn, motorButtonEventHandler, LV_EVENT_CLICKED, this);

    // Create Debug button
    lv_obj_t* debug_btn = lv_btn_create(homeScreen);
    lv_obj_set_size(debug_btn, lv_pct(25), lv_pct(100 / 3));
    lv_obj_align(debug_btn, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_add_style(debug_btn, &screen_btn_style, LV_STATE_DEFAULT);
    lv_obj_set_style_transform_width(debug_btn, 0, LV_STATE_PRESSED);
    lv_obj_set_style_transform_height(debug_btn, 0, LV_STATE_PRESSED);
    lv_obj_set_style_outline_width(debug_btn, 0, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_width(debug_btn, 0, LV_STATE_DEFAULT);

    lv_obj_add_event_cb(debug_btn, dataButtonEventHandler, LV_EVENT_CLICKED, this);

    lv_obj_t* debug_label = lv_label_create(debug_btn);
    lv_label_set_text(debug_label, "Sensor\nData");
    lv_obj_set_style_text_align(debug_label, LV_TEXT_ALIGN_CENTER, LV_STATE_DEFAULT);
    lv_obj_center(debug_label);
    lv_obj_add_style(debug_label, &screen_btn_style, LV_STATE_DEFAULT);

    selected_item_data = NULL;

    lv_scr_load(homeScreen);

}

// Example usage: Apply the color to motor buttons
void updateMotorButtonColor(lv_obj_t* button, double temperature) {
    lv_color_t motorColor = getMotorColor(temperature);
    lv_obj_set_style_bg_color(button, motorColor, LV_STATE_DEFAULT);
}

// Example usage: Apply the color to motor buttons
void updateMotorLabelColor(lv_obj_t* label, double temperature) {
    lv_color_t motorLabelColor = getMotorLabelColor(temperature);
    lv_obj_set_style_text_color(label, motorLabelColor, LV_STATE_DEFAULT);
}

// The motorPage function to display motor data
void Screen::motorPage() {
    motorScreen = lv_obj_create(NULL);
    lv_obj_add_style(motorScreen, &btn_style, LV_STATE_DEFAULT);

    // Create back button
    lv_obj_t* backBtn = lv_btn_create(motorScreen);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(backBtn, lv_pct(100));
    lv_obj_set_style_shadow_width(backBtn, 0, LV_STATE_DEFAULT);
    lv_obj_add_style(backBtn, &screen_btn_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(backBtn, backButtonEventHandler, LV_EVENT_CLICKED, this);
    lv_obj_t* backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);

    // If motors list is empty, show a placeholder
    if (motors.empty()) {
        lv_obj_t* placeholder = lv_list_add_btn(list, NULL, "No motors available");
        lv_obj_add_style(placeholder, &btn_style, LV_STATE_DEFAULT);
        return;
    }

    // Define button size and spacing
    const int button_width = 88;
    const int button_height = 95;
    const int spacing = 10;  // Space between buttons

    // Create motor buttons and labels
    for (size_t i = 0; i < motors.size(); i++) {
        const motor_item_t& motorInfo = motors[i];

        if (motorInfo.motorObject) {
            // Single motor
            lv_obj_t* motorButton = lv_btn_create(motorScreen);
            lv_obj_set_size(motorButton, button_width, button_height);

            double temperature = motorInfo.motorObject->get_temperature();
            updateMotorButtonColor(motorButton, temperature);

            lv_obj_t* motorLabel = lv_label_create(motorButton);
            lv_label_set_text_fmt(motorLabel, "%s: %d°C", motorInfo.motorName, (int)temperature);
            lv_obj_center(motorLabel);

            // Calculate row and column based on index
            int row = i / 5;
            int col = i % 5;
            lv_obj_set_pos(motorButton, col * (button_width + spacing), row * (button_height + spacing) + 40);
        }

        if (motorInfo.motorGroupObject) {
            // MotorGroup - create individual rectangles for each motor in the group
            for (size_t j = 0; j < motorInfo.motorGroupObject->size(); j++) {
                lv_obj_t* motorButton = lv_btn_create(motorScreen);
                lv_obj_set_size(motorButton, button_width, button_height);

                double temperature = motorInfo.motorGroupObject->get_temperature(j);
                updateMotorButtonColor(motorButton, temperature);

                lv_obj_t* motorLabel = lv_label_create(motorButton);
                lv_label_set_text_fmt(motorLabel, "%s %d: %d°C", motorInfo.motorName, j + 1, (int)temperature);
                lv_label_set_long_mode(motorLabel, LV_LABEL_LONG_WRAP);
                lv_obj_set_size(motorLabel, button_width - 5, LV_SIZE_CONTENT);
                lv_obj_center(motorLabel);

                // Calculate row and column for each motor
                int row = (i + j) / 5;  // Adjust row based on group motor count
                int col = (i + j) % 5;  // Adjust column based on group motor count
                lv_obj_set_pos(motorButton, col * (button_width + spacing), row * (button_height + spacing) + 40);
            }
        }
    }
}

// Function to update motor data (called whenever data changes)
void Screen::updateMotorData() {
    for (size_t i = 0; i < motors.size(); i++) {
        lv_obj_t* motorButton = motor_buttons[i];  // Assumes motor_buttons is a stored array of motor buttons

        // Get the latest temperature data from the motor
        double temperature = motors[i].motorObject->get_temperature();

        // Update the button color based on the new temperature
        updateMotorButtonColor(motorButton, temperature);

        // Update the label text with the motor name and the new temperature
        lv_label_set_text_fmt(motor_labels[i], "%s: %.1f°C", motors[i].motorName, temperature);
    }
}

void Screen::logPage(int num_lines) {
    logScreen = lv_obj_create(NULL);
    lv_obj_add_style(logScreen, &btn_style, LV_STATE_DEFAULT);
    // Create back button
    lv_obj_t* backBtn = lv_btn_create(logScreen);
    lv_obj_align(backBtn, LV_ALIGN_TOP_LEFT, 0, 0);
    lv_obj_set_width(backBtn, lv_pct(100));
    lv_obj_set_style_shadow_width(backBtn, 0, LV_STATE_DEFAULT);
    lv_obj_add_style(backBtn, &screen_btn_style, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(backBtn, backButtonEventHandler, LV_EVENT_CLICKED, this);
    lv_obj_t* backLabel = lv_label_create(backBtn);
    lv_label_set_text(backLabel, "Back");
    lv_obj_center(backLabel);
    // Manually position labels below the back button
    int label_start_y = 40; // Starting Y position for labels (adjusted to leave space for the back button)
    int label_spacing = 20; // Vertical spacing between labels

    // Create labels for each line
    for (int i = 0; i < num_lines; i++) {
        lv_obj_t* label = lv_label_create(logScreen);
        lv_label_set_text(label, ""); // Initialize with empty text
        lv_obj_align(label, LV_ALIGN_TOP_LEFT, 10, label_start_y + (i * label_spacing)); // Position each label
        log_labels.push_back(label); // Store the label for later use
    }

}

void Screen::print(int line, const char* fmt, ...) {
    if (line < 0 || line >= log_labels.size()) {
        printf("Error: Invalid line number %d\n", line);
        return;
    }

    char buffer[128]; // Temporary buffer for the formatted string
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, sizeof(buffer), fmt, args); // Format the string
    va_end(args);

    lv_label_set_text(log_labels[line], buffer); // Set the label's text
}


void Screen::logoPage() {
    logoScreen = lv_obj_create(NULL);
    lv_obj_add_style(logoScreen, &btn_style, LV_STATE_DEFAULT);
    lv_obj_t* logoImage = lv_img_create(logoScreen);
    lv_obj_set_size(logoImage, 177, 240);
    lv_img_set_src(logoImage, &logo);
    lv_img_set_zoom(logoImage, 256*0.9);
    lv_obj_align(logoImage, LV_ALIGN_CENTER, 0, 0); // Align it to the center  
}

// Set dark mode style for the interface
void Screen::setDarkModeStyle() {
    lv_style_init(&btn_style);

    lv_style_set_bg_color(&btn_style, lv_color_hex(0x333333));

    lv_style_set_bg_color(&btn_style, lv_color_hex(0x333333));
    lv_style_set_text_color(&btn_style, lv_color_white());

    lv_style_init(&btn_checked_style);
    lv_style_set_bg_color(&btn_checked_style, lv_color_white());
    lv_style_set_text_color(&btn_checked_style, lv_color_black());

    lv_style_init(&list_style);
    lv_style_set_bg_color(&list_style, lv_color_hex(0x333333));
    lv_style_set_text_color(&list_style, lv_color_white());

    lv_style_init(&screen_btn_style);
    lv_style_set_bg_color(&screen_btn_style, lv_color_hex(0x868686));
    lv_style_set_text_color(&screen_btn_style, lv_color_white());
}

void Screen::updateList() {

    if (list == NULL || !lv_obj_is_valid(list)) {
        printf("Error: list is invalid or not created\n");
        return;
    }

    lv_obj_clean(list);

    std::vector<func_item_t> functions = is_blue ? blue_functions : red_functions;

    if (functions.empty()) {
        // Add a placeholder message if the list is empty
        lv_obj_t* placeholder = lv_list_add_btn(list, NULL, "No functions available");
        lv_obj_add_style(placeholder, &btn_style, LV_STATE_DEFAULT);
        return;
    }

    for (size_t i = 0; i < functions.size(); i++) {
        char item_label[50];
        snprintf(item_label, sizeof(item_label), "%s", functions[i].name);

        lv_obj_t* item = lv_list_add_btn(list, NULL, item_label);
        lv_obj_add_style(item, &btn_style, LV_STATE_DEFAULT);
        lv_obj_add_style(item, &btn_checked_style, LV_STATE_CHECKED);
        list_item_data_t* item_data = (list_item_data_t*)malloc(sizeof(list_item_data_t));

        if (!item_data) {
            printf("Error: Memory allocation failed\n");
            return;
        }

        item_data->item = functions[i];
        item_data->list_item = item;

        EventData* event_data = (EventData*)malloc(sizeof(EventData));
        event_data->screen = this;
        event_data->item_data = item_data;

        lv_obj_add_event_cb(item, listItemEventHandler, LV_EVENT_CLICKED, event_data);
    }

    selected_item_data = NULL;
}

// Handle the toggle button click event (Switch between blue and red modes)
void Screen::toggleButtonEventHandler(lv_event_t* e) {
    // Retrieve the Screen object
    Screen* screen = static_cast<Screen*>(lv_event_get_user_data(e));
    lv_obj_t* toggle_btn = lv_event_get_target(e);

    // Access the list object from the Screen instance
    lv_obj_t* list = screen->list;

    // Ensure the list object is valid
    if (list == NULL || !lv_obj_is_valid(list)) {
        printf("Error: list is invalid or not created\n");
        return;
    }

    // Toggle the button appearance and label
    if (screen->is_blue) {
        lv_obj_set_style_bg_color(toggle_btn, lv_color_hex(0xFA4A46), 0); // Red mode
        lv_label_set_text(lv_obj_get_child(toggle_btn, 0), "Red");
    }
    else {
        lv_obj_set_style_bg_color(toggle_btn, lv_color_hex(0x01A0FC), 0); // Blue mode
        lv_label_set_text(lv_obj_get_child(toggle_btn, 0), "Blue");
    }

    // Update the state and refresh the list
    screen->is_blue = !screen->is_blue;
    screen->updateList();
    Intake.setSortColor(screen->getSelectedColor());
}

// Handle list item click event
void Screen::listItemEventHandler(lv_event_t* e) {
    // Retrieve the custom structure holding both screen and item data
    EventData* data = (EventData*)lv_event_get_user_data(e);

    if (!data || !data->item_data || !data->item_data->item.function) {
        printf("Error: Invalid item data or function pointer\n");
        return;
    }

    Screen* screen = data->screen;
    lv_obj_t* item = lv_event_get_target(e);

    if (screen->selected_item_data) {
        lv_obj_clear_state(screen->selected_item_data->list_item, LV_STATE_CHECKED);
    }

    lv_obj_add_state(item, LV_STATE_CHECKED);
    screen->selected_item_data = data->item_data;

    printf("Item selected: %s\n", data->item_data->item.name);
}

void Screen::motorButtonEventHandler(lv_event_t* e) {
    // Retrieve the Screen object
    Screen* screen = static_cast<Screen*>(lv_event_get_user_data(e));
    lv_scr_load(screen->motorScreen);
}

void Screen::backButtonEventHandler(lv_event_t* e) {
    Screen* screen = static_cast<Screen*>(lv_event_get_user_data(e));
    lv_scr_load(screen->homeScreen);
}

void Screen::dataButtonEventHandler(lv_event_t* e) {
    Screen* screen = static_cast<Screen*>(lv_event_get_user_data(e));
    lv_scr_load(screen->logScreen);
}

// Handle the execution of the selected function
void Screen::runSelected() {
    if (selected_item_data && selected_item_data->item.function) {
        selected_item_data->item.function();
    }
    else {
        printf("No function selected!\n");
    }
}

// Add functions to the blue_functions list
void Screen::addBlueFunction(const func_item_t& func) {
    blue_functions.push_back(func);
}

// Add functions to the red_functions list
void Screen::addRedFunction(const func_item_t& func) {
    red_functions.push_back(func);
}

void Screen::addMotor(const motor_item_t& motor) {
    motors.push_back(motor);
}

pros::Color Screen::getSelectedColor() {
    if (is_blue) {
        return pros::Color::blue;
    }
    else {
        return pros::Color::red;
    }
}

void Screen::setPage(Pages newPage) {
    switch (newPage) {
        case HOME:
            printf("Home Selected");
            lv_scr_load(homeScreen);
            break;
        case MOTOR:
            printf("Motor Selected");
            lv_scr_load(motorScreen);
            break;
        case DATA:
            printf("Log Selected");
            lv_scr_load(logScreen);
            break;
        case LOGO:
            printf("Logo Selected");
            lv_scr_load(logoScreen);
            break;
    }
}
