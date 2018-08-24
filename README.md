# Treadmill Hack

Controlling treadmill speed and slope directly using Arduino UNO

## Usage

- upload code to Arduino UNO

- open Serial Monitor

- to change the slope of the treadmill: send `up` or `dn` via Serial

- to set new PWM value: send `p<pwm>` via Serial, where `<pwm>` is an integer in the range of 0 to 49 (default PWM on start-up is 0)
