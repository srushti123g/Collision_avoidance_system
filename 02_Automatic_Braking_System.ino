// Created by LecrinTech, India.  
/*
 *  Automatic Braking System
 *  
 *  Overview:
 *  This system automatically applies brakes when an obstacle is detected within a threshold distance.
 *  - An ultrasonic sensor measures the distance to the obstacle (Trig D6, Echo D5).
 *  - A servo motor (D8) is used to engage the brake.
 *  - A buzzer (D3) provides a warning signal (Active Low).
 *  - An LED (D4) blinks as a visual warning (Active Low).
 *  
 *  Logic:
 *  - If an obstacle is detected within 150mm, the buzzer beeps and LED blinks.
 *  - The beep and blink rate increase as the obstacle gets closer.
 *  - If the distance reaches 70mm (brake threshold), the servo moves from 0° to 90°, applying the brake.
 *  - The buzzer remains continuously ON for 500ms during braking, then turns OFF.
 *  
 *  Components:
 *  - Hedy MCU (ESP8266)
 *  - Ultrasonic Sensor (HC-SR04) [Trig: D6, Echo: D5]
 *  - Servo Motor (D8)
 *  - Buzzer (D3, Active Low)
 *  - LED Indicator (D4, Active Low)
 */

#include <Servo.h>

#define TRIG_PIN D6       // Ultrasonic sensor trigger pin
#define ECHO_PIN D5       // Ultrasonic sensor echo pin
#define SERVO_PIN D8      // Servo motor control pin
#define BUZZER D3         // Buzzer (Active Low)
#define LED_PIN D4        // LED Indicator (Active Low)

#define DISTANCE_THRESHOLD 150  // Warning starts at this distance (mm)
#define BRAKE_THRESHOLD 70      // Brake engages at this distance (mm)
#define BEEP_DELAY 200          // Beep delay in milliseconds

Servo brakeServo;

void setup() 
{
    Serial.begin(115200); // Initialize serial communication for debugging
    
    pinMode(TRIG_PIN, OUTPUT);   // Configure ultrasonic trigger pin as output
    pinMode(ECHO_PIN, INPUT);    // Configure ultrasonic echo pin as input
    pinMode(BUZZER, OUTPUT);     // Configure buzzer pin as output
    pinMode(LED_PIN, OUTPUT);    // Configure LED pin as output
    
    brakeServo.attach(SERVO_PIN, 500, 2400); // Attach servo with defined pulse width range
    brakeServo.write(0);          // Set initial servo position (0° - No brake)
    
    digitalWrite(BUZZER, HIGH);   // Ensure buzzer is OFF at startup
    digitalWrite(LED_PIN, HIGH);  // Ensure LED is OFF at startup
    
    Serial.println("Automatic Braking System Initialized");
}

void loop() 
{   
    long distance = measureDistance(); // Measure the obstacle distance
    Serial.print("Obstacle Distance: ");
    Serial.print(distance);
    Serial.println(" mm");

    if (distance <= BRAKE_THRESHOLD) // If distance reaches braking point
    {  
        Serial.println("Obstacle too close! Applying brakes...");
        applyBrakes();
    }
    else if (distance <= DISTANCE_THRESHOLD) // If within warning zone
    {
        Serial.println("Warning! Obstacle detected in range.");
        warningSignal(distance);
    }
    else // If safe distance
    {
        Serial.println("Safe distance maintained.");
        digitalWrite(BUZZER, HIGH); // Turn OFF buzzer
        digitalWrite(LED_PIN, HIGH); // Turn OFF LED
        brakeServo.write(0);         // Ensure brake is released
    }
  
}

long measureDistance() 
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    
    long duration = pulseIn(ECHO_PIN, HIGH);
    return (duration * 0.343) / 2; // Convert duration to distance in mm
}

void applyBrakes()
{
    digitalWrite(BUZZER, LOW); // Activate buzzer (Active Low)
    digitalWrite(LED_PIN, LOW); // Activate LED (Active Low)
    brakeServo.write(90);       // Move servo to 90° to engage brake
    delay(500);                 // Hold brake position
    digitalWrite(BUZZER, HIGH); // Turn OFF buzzer after braking
}

void warningSignal(long distance)
{
    int beepDelay = map(distance, BRAKE_THRESHOLD, DISTANCE_THRESHOLD, 50, 500);
    digitalWrite(BUZZER, LOW); // Activate buzzer (Active Low)
    digitalWrite(LED_PIN, LOW); // Activate LED (Active Low)
    delay(beepDelay);
    digitalWrite(BUZZER, HIGH); // Deactivate buzzer
    digitalWrite(LED_PIN, HIGH); // Deactivate LED
    delay(beepDelay);
}
