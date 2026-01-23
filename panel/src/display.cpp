#include <ArduinoEigen.h>
#include "constants.h"
#include "display.h"

typedef struct {
    uint8_t i;
    uint8_t j;
} index_t;

index_t sch_to_pos_index(index_t sch_index);


Display::Display(queue_t &display_queue) : display_queue_(display_queue) {}

void Display::initialize() {
    col_pin_mask_ = 0;
    for (size_t i=0; i<COL_PIN.size(); i++) {
        gpio_init(COL_PIN(i));
        col_pin_mask_ |= (uint64_t(1) << COL_PIN(i));
    }
    row_pin_mask_ = 0;
    for (size_t i=0; i<ROW_PIN.size(); i++) {
        gpio_init(ROW_PIN(i));
        row_pin_mask_ |= (uint64_t(1) << ROW_PIN(i));
    }

    gpio_set_dir_out_masked64(col_pin_mask_);
    gpio_clr_mask64(col_pin_mask_);

    gpio_set_dir_out_masked64(row_pin_mask_);
    gpio_set_mask64(row_pin_mask_);
}

void Display::update() {
    
    if (!queue_is_empty(&display_queue_)) { 
        queue_try_remove(&display_queue_, &pat_);
        show();

    }
}

void Display::show() {

    Eigen::Vector<uint8_t, PANEL_SIZE> pixel_value; 
    Eigen::Vector<uint64_t, MAX_GRAY_LEVEL> col_clr_mask;
    uint8_t num_gray_level = GRAY_LEVEL_UMAP.at(pat_.gray_level());

    // Kludgey gray level delay
    size_t gray_level_delay = 0;
    switch (pat_.gray_level()) {
        case GrayLevel::Gray_2:
            gray_level_delay = 500;
            break;
        case GrayLevel::Gray_16:
            gray_level_delay = 100;
            break;
    }

    gpio_set_mask64(row_pin_mask_);
    for (size_t i=0; i<ROW_PIN.size(); i++) {
        uint64_t col_set_mask = 0;
        col_clr_mask.setZero();
        for (size_t j=0; j<COL_PIN.size(); j++) {
            index_t sch_index {uint8_t(i), uint8_t(j)};
            index_t pos_index = sch_to_pos_index(sch_index);
            pixel_value(j) = pat_.matrix()(pos_index.i, pos_index.j); 
            if (pixel_value(j) > 0) {
                digitalWrite(COL_PIN(j), HIGH); 
                col_set_mask |= uint64_t(1) << COL_PIN(j);
                uint32_t mask_ind = min(pixel_value(j), num_gray_level-1); 
                col_clr_mask(mask_ind) |= uint64_t(1) << COL_PIN(j);
            }
        }
        gpio_put(ROW_PIN(i),0);
        gpio_set_mask64(col_set_mask);
        volatile uint8_t tmp = 0;
        for (size_t k=0; k<num_gray_level; k++) {
            // Delay loop. Super kludgey. Need to do better timing.
            for (size_t kk=0; kk<gray_level_delay; kk++) {
                tmp++;
            }
            gpio_clr_mask64(col_clr_mask(k));
        }
        gpio_clr_mask64(col_set_mask);
        gpio_put(ROW_PIN(i), 1);
    }
}


index_t sch_to_pos_index(index_t sch_index) {
    index_t pos_index;
    if (sch_index.j % NUM_COLOR < NUM_COLOR/2) {
        if (sch_index.i < PANEL_SIZE/2) {
            pos_index.i = 2*sch_index.i;
            pos_index.j = sch_index.j;
        }
        else {
            pos_index.i = 2*(PANEL_SIZE - (sch_index.i+1));
            pos_index.j = NUM_COLOR/2 + sch_index.j;
        }
    }
    else {
        if (sch_index.i < PANEL_SIZE/2) {
            pos_index.i = 2*sch_index.i + 1;
            pos_index.j = sch_index.j - NUM_COLOR/2;
        }
        else {
            pos_index.i = 2*(PANEL_SIZE - (sch_index.i+1)) + 1;
            pos_index.j = sch_index.j;
        }
    }
    return pos_index;
}
