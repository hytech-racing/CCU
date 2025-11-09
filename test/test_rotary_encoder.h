#ifndef TEST_ROTARY_ENCODER_H
#define TEST_ROTARY_ENCODER_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "RotaryEncoderInterface.h"
#include "CCUData.h"

using ::testing::Return;

class RotaryEncoderTest : public ::testing::Test {
protected:
    CCUData ccu_data;
    RotaryEncoderInterface encoder{ccu_data};
    
    void SetUp() override {
        // Reset CCUData before each test
        ccu_data.encoder_value = 0;
        encoder.setupEncoder();
    }

    // Helper to simulate encoder update cycle
    void rotateEncoder(int direction) {
        encoder.set_enc_value(direction);
        encoder.updateEncoder();
    }
};

// Test: Encoder increments on positive DT value (HIGH=1)
TEST_F(RotaryEncoderTest, IncrementOnClockwise) {
    float initial_value = ccu_data.encoder_value;
    rotateEncoder(HIGH);
    
    EXPECT_EQ(ccu_data.encoder_value, initial_value + 1);
}

// Test: Encoder decrements on negative DT value (LOW=0)
TEST_F(RotaryEncoderTest, DecrementOnCounterClockwise) {
    // ccu_data encoder value initially at 0, so we need to set it to 1 so it can decrement properly
    rotateEncoder(HIGH);
    float initial_value = ccu_data.encoder_value;
    rotateEncoder(LOW);
    
    EXPECT_EQ(ccu_data.encoder_value, initial_value - 1);
}

// Test: Multiple increments in sequence
TEST_F(RotaryEncoderTest, MultipleClockwiseSteps) {
    for (int i = 0; i < 5; i++) {
        rotateEncoder(HIGH);
    }
    
    EXPECT_EQ(ccu_data.encoder_value, 5.0f);
}

// Test: Multiple decrements in sequence
TEST_F(RotaryEncoderTest, MultipleCounterClockwiseSteps) {
    // First increment to 10
    for (int i = 0; i < 10; i++) {
        rotateEncoder(HIGH);
    }
    EXPECT_EQ(ccu_data.encoder_value, 10.0f);
    
    // Now decrement by 3
    for (int i = 0; i < 3; i++) {
        rotateEncoder(LOW);
    }
    
    EXPECT_EQ(ccu_data.encoder_value, 7.0f);
}

// Test: Button press returns initial state
TEST_F(RotaryEncoderTest, ButtonInitiallyNotPressed) {
    EXPECT_FALSE(encoder.isButtonPressed());
}

// Test: Alternating CW and CCW rotations
TEST_F(RotaryEncoderTest, AlternatingDirections) {
    rotateEncoder(HIGH);   // +1
    rotateEncoder(HIGH);   // +1
    rotateEncoder(LOW);    // -1
    rotateEncoder(LOW);    // -1
    rotateEncoder(HIGH);   // +1
    
    EXPECT_EQ(ccu_data.encoder_value, 1.0f);
}

// Test: Maximum value clamping at 120
TEST_F(RotaryEncoderTest, MaxValueClamping) {
    // Increment to 120
    for (int i = 0; i < 120; i++) {
        rotateEncoder(HIGH);
    }
    EXPECT_EQ(ccu_data.encoder_value, 120.0f);
    
    // Try to increment beyond max
    rotateEncoder(HIGH);
    
    // Should stay at 120, not exceed
    EXPECT_EQ(ccu_data.encoder_value, 120.0f);
}

// Test: Minimum value clamping at 0
TEST_F(RotaryEncoderTest, MinValueClamping) {
    // Already at 0 from SetUp
    EXPECT_EQ(ccu_data.encoder_value, 0.0f);
    
    rotateEncoder(LOW);
    
    // Should stay at 0, not go negative
    EXPECT_EQ(ccu_data.encoder_value, 0.0f);
}

// Test: Full range sweep from 0 to max
TEST_F(RotaryEncoderTest, FullRangeClockwise) {
    ccu_data.encoder_value = 0.0f;
    
    for (int i = 0; i < 120; i++) {
        rotateEncoder(HIGH);
    }
    
    EXPECT_EQ(ccu_data.encoder_value, 120.0f);
}

// Test: Full range sweep from max to 0
TEST_F(RotaryEncoderTest, FullRangeCounterClockwise) {
    // First go to 120
    for (int i = 0; i < 120; i++) {
        rotateEncoder(HIGH);
    }
    EXPECT_EQ(ccu_data.encoder_value, 120.0f);
    
    // Now go back to 0
    for (int i = 0; i < 120; i++) {
        rotateEncoder(LOW);
    }
    
    EXPECT_EQ(ccu_data.encoder_value, 0.0f);
}

// Test: Value stays within valid range during complex rotation pattern
TEST_F(RotaryEncoderTest, BoundaryBehaviorComplex) {
    // First go to 118
    for (int i = 0; i < 118; i++) {
        rotateEncoder(HIGH);
    }
    
    rotateEncoder(HIGH);   // 119
    rotateEncoder(HIGH);   // 120
    rotateEncoder(HIGH);   // 120 (clamped)
    rotateEncoder(LOW);    // 119
    rotateEncoder(LOW);    // 118
    
    EXPECT_EQ(ccu_data.encoder_value, 118.0f);
}

#endif // TEST_ROTARY_ENCODER_H
