#ifndef PATTERN_H
#define PATTERN_H
#include <ArduinoEigen.h>
#include "constants.h"

typedef Eigen::Matrix<uint8_t, PANEL_SIZE, PANEL_SIZE> Matrix; 

class Pattern {

    public:
        Pattern();

    protected:
        Matrix matrix_ = Matrix::Zero();
        GrayLevel gray_level_ = GrayLevel::None;

};

#endif
