# PLC Text Language — Complete V1 Specification

## 1. Purpose

This language is a text-based PLC programming language designed to control industrial automation systems.

The programmer describes:

* Physical inputs and outputs
* Internal variables
* Machine logic
* Timers
* Counters
* Sequences
* States
* Alarms
* Analog signals
* Communication
* Functions

The language hides hardware-specific operations behind readable PLC instructions.

Example:

```text
IF START AND NOT STOP THEN
    MOTOR = ON
END
```

instead of directly manipulating ESP32 GPIOs.

---

# 2. Program Structure

A program has this general structure:

```text
PROGRAM Conveyor

VARIABLES

    ...

END

FUNCTIONS

    ...

END

PROGRAM

    ...

END
```

`VARIABLES` contains all variable declarations.

`FUNCTIONS` contains optional user-defined functions.

The second `PROGRAM` section contains the machine logic.

---

# 3. Comments

Single-line comments begin with `#`.

```text
# Start button
START : INPUT I0

# Conveyor motor
MOTOR : OUTPUT Q0
```

The interpreter ignores everything from `#` until the end of the line.

---

# 4. Identifiers

Identifiers are names given to variables, states, functions, and other objects.

Valid:

```text
START
MOTOR
MOTOR_1
CONVEYOR_SPEED
Temperature
```

Invalid:

```text
1MOTOR
MOTOR-SPEED
MOTOR SPEED
```

Identifiers are case-insensitive.

Therefore:

```text
MOTOR
motor
Motor
```

refer to the same identifier.

---

# 5. Variable System

All variables are declared in the `VARIABLES` section.

General syntax:

```text
NAME : TYPE
```

Hardware variables use:

```text
NAME : TYPE ADDRESS
```

Example:

```text
VARIABLES

    START  : INPUT I0
    STOP   : INPUT I1
    MOTOR  : OUTPUT Q0

    RUNNING : BOOL
    SPEED   : INT
    TEMP    : REAL

END
```

---

# 6. Variable Types

The language supports:

```text
INPUT
OUTPUT

BOOL
INT
REAL

TIMER
COUNTER

STRING
```

---

# 7. Digital Inputs

An `INPUT` represents a physical digital input.

```text
START : INPUT I0
```

The variable automatically reflects the physical input.

Usage:

```text
IF START THEN
    ...
END
```

An input can be:

```text
TRUE
```

or:

```text
FALSE
```

Inputs are read at the beginning of every PLC scan.

---

# 8. Digital Outputs

An `OUTPUT` represents a physical digital output.

```text
MOTOR : OUTPUT Q0
```

Output control:

```text
MOTOR ON
```

```text
MOTOR OFF
```

or:

```text
MOTOR = TRUE
MOTOR = FALSE
```

The physical outputs are updated after the program execution phase.

---

# 9. Boolean Variables

A `BOOL` stores:

```text
TRUE
FALSE
```

Example:

```text
RUNNING : BOOL = FALSE
FAULT   : BOOL = FALSE
READY   : BOOL = TRUE
```

Assignment:

```text
RUNNING = TRUE
```

```text
FAULT = FALSE
```

---

# 10. Integer Variables

`INT` stores whole numbers.

```text
SPEED : INT = 0
COUNT : INT = 10
```

Operations:

```text
SPEED = SPEED + 10
COUNT = COUNT - 1
```

---

# 11. Real Variables

`REAL` stores decimal values.

```text
TEMPERATURE : REAL = 20.5
VOLTAGE     : REAL = 24.0
PRESSURE    : REAL = 3.5
```

Example:

```text
IF TEMPERATURE > 80.0 THEN
    FAN ON
END
```

---

# 12. Strings

`STRING` stores text.

```text
NAME : STRING = "MOTOR"
```

Example:

```text
MESSAGE : STRING = "System Ready"
```

Strings can be used for:

* Messages
* Machine names
* Debug information
* Communication

---

# 13. Default Values

Variables can have an initial value.

```text
RUNNING : BOOL = FALSE
SPEED   : INT = 0
TEMP    : REAL = 20.0
NAME    : STRING = "PLC"
```

If no value is specified, the runtime initializes the variable according to its type.

---

# 14. Constants

Constants cannot be changed during program execution.

Syntax:

```text
CONST NAME : TYPE = VALUE
```

Example:

```text
CONST MAX_SPEED : INT = 100
CONST MAX_TEMP : REAL = 80.0
```

Usage:

```text
IF SPEED > MAX_SPEED THEN
    MOTOR OFF
END
```

---

# 15. Assignment

Variables are assigned using `=`.

```text
SPEED = 50
RUNNING = TRUE
TEMP = 25.5
```

Expressions can also be assigned:

```text
SPEED = SPEED + 10
TOTAL = COUNT * 5
```

---

# 16. Arithmetic Operators

Supported operators:

```text
+
-
*
/
%
```

Examples:

```text
A = B + C
A = B - C
A = B * C
A = B / C
A = B % C
```

`%` returns the remainder.

Example:

```text
REMAINDER = 10 % 3
```

Result:

```text
1
```

---

# 17. Comparison Operators

Supported:

```text
==
!=
>
<
>=
<=
```

Examples:

```text
IF SPEED == 100 THEN
END
```

```text
IF SPEED != 0 THEN
END
```

```text
IF TEMP > 80.0 THEN
END
```

---

# 18. Logical Operators

Supported:

```text
AND
OR
NOT
```

Example:

```text
IF START AND READY THEN
    MOTOR ON
END
```

Example:

```text
IF START OR REMOTE_START THEN
    MOTOR ON
END
```

Example:

```text
IF NOT FAULT THEN
    MOTOR ON
END
```

Parentheses are supported:

```text
IF (START OR REMOTE_START) AND NOT STOP THEN
    MOTOR ON
END
```

---

# 19. Operator Precedence

From highest to lowest:

```text
()
NOT
*
/
%
+
-
==
!=
>
<
>=
<=
AND
OR
```

Parentheses can always be used to make an expression explicit.

---

# 20. IF

Basic conditional:

```text
IF condition THEN

    instructions

END
```

Example:

```text
IF START THEN
    MOTOR ON
END
```

---

# 21. ELSE

```text
IF condition THEN

    instructions

ELSE

    instructions

END
```

Example:

```text
IF START THEN
    MOTOR ON
ELSE
    MOTOR OFF
END
```

---

# 22. ELSE IF

Multiple conditions can be chained.

```text
IF SPEED > 80 THEN

    FAN ON

ELSE IF SPEED > 40 THEN

    FAN OFF

ELSE

    MOTOR OFF

END
```

---

# 23. Nested Conditions

Conditions can contain other conditions.

```text
IF START THEN

    IF NOT FAULT THEN

        MOTOR ON

    ELSE

        MOTOR OFF

    END

END
```

---

# 24. Digital Output Commands

The language provides simple output commands:

```text
MOTOR ON
MOTOR OFF
```

Equivalent Boolean assignments:

```text
MOTOR = TRUE
MOTOR = FALSE
```

---

# 25. Timers

Timers are declared as:

```text
T1 : TIMER
```

A timer can be started with:

```text
START T1 5s
```

Supported time units:

```text
ms
s
min
```

Examples:

```text
START T1 500ms
START T2 5s
START T3 2min
```

---

# 26. Timer Properties

A timer provides:

```text
T1.DONE
T1.RUNNING
T1.REMAINING
T1.ELAPSED
```

Example:

```text
IF T1.DONE THEN
    MOTOR ON
END
```

---

# 27. Timer Reset

```text
RESET T1
```

Example:

```text
IF STOP THEN
    RESET T1
END
```

---

# 28. TON Timer

A TON timer turns its `DONE` status on after the input condition has remained active for the preset time.

Conceptually:

```text
START
  │
  └──> TIMER 5s
           │
           └──> DONE
```

Language:

```text
TON T1 5s WHEN START
```

Then:

```text
IF T1.DONE THEN
    MOTOR ON
END
```

---

# 29. TOF Timer

A TOF timer keeps its output active for a specified time after its input becomes false.

```text
TOF T1 5s WHEN START
```

---

# 30. Pulse Timer

A pulse timer produces a fixed-duration pulse.

```text
TP T1 2s WHEN SENSOR
```

When `SENSOR` becomes active, `T1` runs for 2 seconds.

---

# 31. Counters

Declare:

```text
PARTS : COUNTER
```

Increment:

```text
PARTS++
```

Decrement:

```text
PARTS--
```

Reset:

```text
RESET PARTS
```

Example:

```text
IF SENSOR RISING THEN
    PARTS++
END
```

---

# 32. Counter Properties

A counter provides:

```text
PARTS.VALUE
PARTS.ZERO
PARTS.DONE
```

Example:

```text
IF PARTS.VALUE >= 10 THEN
    MOTOR OFF
END
```

---

# 33. Preset Counters

A counter can have a preset:

```text
PARTS : COUNTER 10
```

Then:

```text
IF PARTS.DONE THEN
    MOTOR OFF
END
```

`DONE` becomes true when the counter reaches its preset.

---

# 34. Edge Detection

Digital signals support:

```text
RISING
FALLING
```

Rising:

```text
IF SENSOR RISING THEN
    PARTS++
END
```

Falling:

```text
IF SENSOR FALLING THEN
    ALARM ON
END
```

A rising edge means:

```text
FALSE → TRUE
```

A falling edge means:

```text
TRUE → FALSE
```

---

# 35. One-Shot

A one-shot executes an action once when a condition becomes true.

```text
ONCE START THEN
    COUNTER++
END
```

This is equivalent to detecting a rising edge on `START`.

---

# 36. States

States describe different stages of a machine.

Syntax:

```text
STATE NAME

    ...

END
```

Example:

```text
STATE IDLE

    MOTOR OFF

END
```

---

# 37. State Transitions

Use:

```text
GOTO STATE
```

Example:

```text
STATE IDLE

    IF START THEN
        GOTO RUNNING
    END

END
```

Another state:

```text
STATE RUNNING

    MOTOR ON

    IF STOP THEN
        GOTO IDLE
    END

END
```

---

# 38. Initial State

The first state can be declared:

```text
INITIAL IDLE
```

Example:

```text
INITIAL IDLE

STATE IDLE

    MOTOR OFF

    IF START THEN
        GOTO RUNNING
    END

END
```

---

# 39. State Entry

A state can contain an entry section:

```text
STATE FILLING

    ENTER
        RESET TIMER
    END

    ...

END
```

The `ENTER` section executes once when entering the state.

---

# 40. State Exit

A state can contain an exit section:

```text
STATE FILLING

    ...

    EXIT
        PUMP OFF
    END

END
```

The `EXIT` section executes when leaving the state.

---

# 41. State Example

```text
INITIAL WAITING

STATE WAITING

    MOTOR OFF
    PUMP OFF

    IF START THEN
        GOTO FILLING
    END

END


STATE FILLING

    PUMP ON

    IF LEVEL_HIGH THEN
        GOTO MOVING
    END

    IF STOP THEN
        GOTO WAITING
    END

END


STATE MOVING

    MOTOR ON

    IF SENSOR THEN
        GOTO WAITING
    END

END
```

This represents:

```text
WAITING
   ↓
FILLING
   ↓
MOVING
   ↓
WAITING
```

---

# 42. Functions

Functions allow reusable pieces of logic.

Syntax:

```text
FUNCTION NAME()

    ...

END
```

Example:

```text
FUNCTION STOP_MACHINE()

    MOTOR OFF
    PUMP OFF
    RUNNING = FALSE

END
```

Call:

```text
STOP_MACHINE()
```

---

# 43. Function Parameters

Functions can receive values.

```text
FUNCTION SET_SPEED(VALUE : INT)

    SPEED = VALUE

END
```

Call:

```text
SET_SPEED(50)
```

---

# 44. Function Return Values

Functions can return values.

```text
FUNCTION DOUBLE(VALUE : INT) : INT

    RETURN VALUE * 2

END
```

Usage:

```text
RESULT = DOUBLE(10)
```

---

# 45. Local Variables

Functions can have local variables.

```text
FUNCTION CALCULATE()

    LOCAL TEMP : INT

    TEMP = SPEED * 2

    RETURN TEMP

END
```

Local variables exist only while the function is executing.

---

# 46. Arrays

Arrays store multiple values.

Declaration:

```text
SPEEDS : INT[10]
```

Access:

```text
SPEEDS[0]
SPEEDS[1]
SPEEDS[2]
```

Assignment:

```text
SPEEDS[0] = 50
```

---

# 47. Array Size

Array indexes start at `0`.

For:

```text
VALUES : INT[5]
```

valid indexes are:

```text
0
1
2
3
4
```

---

# 48. Analog Inputs

Analog inputs can be declared:

```text
TEMP : ANALOG_INPUT AI0
```

Example:

```text
IF TEMP > 80.0 THEN
    FAN ON
END
```

Analog values are represented as numeric values.

---

# 49. Analog Outputs

Analog outputs:

```text
SPEED : ANALOG_OUTPUT AO0
```

Example:

```text
SPEED = 75.0
```

---

# 50. Scaling

Raw analog values can be converted into engineering units.

Example:

```text
PRESSURE : ANALOG_INPUT AI0
```

Scaling:

```text
SCALE PRESSURE
    RAW 0..4095
    VALUE 0.0..10.0
END
```

The resulting value is available as:

```text
PRESSURE
```

---

# 51. Alarms

Alarms can be declared:

```text
ALARM OVER_TEMP
```

Trigger:

```text
RAISE OVER_TEMP
```

Clear:

```text
CLEAR OVER_TEMP
```

Check:

```text
IF OVER_TEMP THEN
    MOTOR OFF
END
```

---

# 52. Faults

Faults represent machine fault conditions.

```text
FAULT MOTOR_FAULT
```

Raise:

```text
RAISE MOTOR_FAULT
```

Clear:

```text
CLEAR MOTOR_FAULT
```

Example:

```text
IF OVERLOAD THEN
    RAISE MOTOR_FAULT
END
```

---

# 53. Fault Handling

A fault can stop an output:

```text
IF MOTOR_FAULT THEN
    MOTOR OFF
END
```

Multiple faults:

```text
IF MOTOR_FAULT OR OVER_TEMP OR ESTOP THEN
    MOTOR OFF
END
```

---

# 54. Communication Variables

Communication variables allow external devices to interact with the PLC.

Example:

```text
REMOTE_START : BOOL
REMOTE_SPEED : INT
```

These can later be mapped to protocols such as:

```text
MODBUS
CAN
ETHERNET
RS485
```

The language itself does not need to expose the low-level communication implementation.

---

# 55. Modbus

A future Modbus declaration could look like:

```text
MODBUS DEVICE DRIVE

    ADDRESS 1
    REGISTER SPEED
    REGISTER STATUS

END
```

Then:

```text
DRIVE.SPEED = 50
```

and:

```text
IF DRIVE.STATUS == 1 THEN
    ...
END
```

---

# 56. Hardware Mapping

The variable table separates the machine program from the hardware.

Example:

```text
VARIABLES

    START : INPUT I0
    MOTOR : OUTPUT Q0

END
```

The program only uses:

```text
START
MOTOR
```

It does not need to know that `MOTOR` is physically connected to `Q0`.

This makes hardware changes easier.

---

# 57. Aliases

A physical address can have a meaningful name.

```text
MOTOR : OUTPUT Q0
```

means:

```text
MOTOR → Q0
```

The program uses:

```text
MOTOR
```

not:

```text
Q0
```

---

# 58. Groups

Variables can optionally be grouped.

```text
VARIABLES

    INPUTS

        START : INPUT I0
        STOP  : INPUT I1
        SENSOR : INPUT I2

    END

    OUTPUTS

        MOTOR : OUTPUT Q0
        PUMP  : OUTPUT Q1

    END

END
```

The groups are organizational and do not change execution.

---

# 59. PLC Scan Cycle

The runtime operates cyclically.

Each scan follows:

```text
1. Read physical inputs
2. Update INPUT variables
3. Process timers
4. Process counters
5. Execute PROGRAM
6. Update outputs
7. Process communication
8. Repeat
```

Conceptually:

```text
        ┌───────────────┐
        │ READ INPUTS   │
        └───────┬───────┘
                ↓
        ┌───────────────┐
        │ UPDATE TIMERS │
        │ & COUNTERS    │
        └───────┬───────┘
                ↓
        ┌───────────────┐
        │ EXECUTE       │
        │ PROGRAM       │
        └───────┬───────┘
                ↓
        ┌───────────────┐
        │ WRITE OUTPUTS │
        └───────┬───────┘
                ↓
             REPEAT
```

---

# 60. Execution Order

Statements execute from top to bottom.

Example:

```text
MOTOR ON
MOTOR OFF
```

The final state of `MOTOR` after that scan is:

```text
OFF
```

Therefore programs should be structured so that conflicting commands are avoided.

---

# 61. Input Image

Physical inputs are copied into an internal input table at the beginning of the scan.

Example:

```text
I0 = HIGH
```

becomes:

```text
START = TRUE
```

The program then reads `START`.

---

# 62. Output Image

Output commands modify an internal output table.

Example:

```text
MOTOR ON
```

changes:

```text
Q0 = TRUE
```

The physical output is updated after program execution.

This prevents the program from directly manipulating hardware in the middle of the scan.

---

# 63. Variable Table Internally

The ESP32 creates a symbol table when loading the program.

For:

```text
START : INPUT I0
MOTOR : OUTPUT Q0
SPEED : INT
```

the interpreter internally creates something conceptually like:

```text
ID     NAME      TYPE      ADDRESS
0      START     INPUT     I0
1      MOTOR     OUTPUT    Q0
2      SPEED     INT       -
```

The program can then reference variables using their IDs.

This is much faster than repeatedly searching for the variable name during every scan.

---

# 64. Program Loading

The ESP32 receives:

```text
PROGRAM TEXT
```

The runtime performs:

```text
TEXT
 ↓
LEXER
 ↓
TOKENS
 ↓
PARSER
 ↓
VARIABLE TABLE
 ↓
PROGRAM INSTRUCTIONS
 ↓
VALIDATION
 ↓
RUN
```

---

# 65. Lexer

The lexer converts text into tokens.

For:

```text
MOTOR ON
```

the lexer produces approximately:

```text
IDENTIFIER(MOTOR)
KEYWORD(ON)
```

For:

```text
IF START AND NOT STOP THEN
```

it produces:

```text
IF
IDENTIFIER(START)
AND
NOT
IDENTIFIER(STOP)
THEN
```

---

# 66. Parser

The parser checks whether the tokens follow the language rules.

Example:

```text
IF START THEN
    MOTOR ON
END
```

is valid.

But:

```text
IF START
    MOTOR ON
```

is invalid because `THEN` is missing.

---

# 67. Semantic Validation

After parsing, the interpreter checks whether the program makes sense.

For example:

```text
MOTOR : OUTPUT Q0
```

then:

```text
MOTOR ON
```

is valid.

But:

```text
MOTOR++
```

is invalid because `MOTOR` is an output, not a counter.

Likewise:

```text
START = 50
```

is invalid because `START` is an input.

---

# 68. Runtime Errors

The PLC should detect errors such as:

```text
Unknown variable
Invalid variable type
Invalid hardware address
Missing END
Invalid expression
Invalid state
Array out of bounds
Division by zero
Invalid timer
Invalid function
```

The runtime should report the line number.

Example:

```text
ERROR 24:
Cannot assign INT value to INPUT variable START.
```

---

# 69. Program States

The PLC runtime itself has several modes:

```text
STOPPED
LOADING
RUNNING
ERROR
```

A program must successfully parse and validate before entering:

```text
RUNNING
```

---

# 70. STOP

The PLC can stop program execution:

```text
STOP
```

When stopped, outputs should enter their configured safe state.

---

# 71. START

The PLC can start the loaded program:

```text
RUN
```

The program then enters its scan cycle.

---

# 72. RESET

System reset:

```text
RESET
```

can reset:

* Internal variables
* Timers
* Counters
* States
* Faults

according to the configured reset behavior.

---

# 73. Complete Example

```text
PROGRAM BottleMachine


VARIABLES

    # Inputs

    START       : INPUT I0
    STOP        : INPUT I1
    BOTTLE      : INPUT I2
    LEVEL_HIGH  : INPUT I3
    ESTOP       : INPUT I4


    # Outputs

    CONVEYOR    : OUTPUT Q0
    PUMP        : OUTPUT Q1
    VALVE       : OUTPUT Q2
    ALARM       : OUTPUT Q3


    # Internal variables

    RUNNING     : BOOL = FALSE
    FULL        : BOOL = FALSE

    BOTTLES     : COUNTER = 0

    FILL_TIMER  : TIMER
    DELAY_TIMER : TIMER


    # Constants

    CONST MAX_BOTTLES : INT = 10

END


PROGRAM


    # Emergency stop

    IF ESTOP THEN

        CONVEYOR OFF
        PUMP OFF
        VALVE OFF

        RUNNING = FALSE

        GOTO SAFE

    END


    # Start machine

    IF START AND NOT STOP THEN
        RUNNING = TRUE
    END


    # Stop machine

    IF STOP THEN
        RUNNING = FALSE
    END


    # Main machine

    IF RUNNING THEN

        CONVEYOR ON

    ELSE

        CONVEYOR OFF
        PUMP OFF
        VALVE OFF

    END


    # Detect bottle

    IF BOTTLE RISING THEN

        CONVEYOR OFF

        START DELAY_TIMER 500ms

        GOTO FILL

    END


    # Count bottles

    IF BOTTLE RISING THEN
        BOTTLES++
    END


    # Maximum production

    IF BOTTLES >= MAX_BOTTLES THEN

        RUNNING = FALSE
        FULL = TRUE

    END


STATE FILL


    CONVEYOR OFF

    IF DELAY_TIMER.DONE THEN

        VALVE ON
        PUMP ON

        START FILL_TIMER 5s

        GOTO FILLING

    END


STATE FILLING


    PUMP ON
    VALVE ON

    IF LEVEL_HIGH THEN

        PUMP OFF
        VALVE OFF

        GOTO RUNNING

    END


    IF FILL_TIMER.DONE THEN

        PUMP OFF
        VALVE OFF

        RAISE FILL_FAULT

        GOTO SAFE

    END


STATE SAFE


    CONVEYOR OFF
    PUMP OFF
    VALVE OFF

    IF NOT ESTOP THEN
        CLEAR FILL_FAULT
        GOTO WAITING
    END


STATE WAITING


    CONVEYOR OFF
    PUMP OFF
    VALVE OFF

    IF START THEN
        RUNNING = TRUE
        GOTO RUNNING
    END


STATE RUNNING


    CONVEYOR ON

    IF STOP THEN
        GOTO WAITING
    END

END
```

---

# 74. Minimal Language

Although V1 supports many features, the first ESP32 implementation should not implement everything at once.

The minimum executable language should be:

```text
PROGRAM
VARIABLES

INPUT
OUTPUT
BOOL
INT

IF
ELSE
THEN
END

AND
OR
NOT

ON
OFF

=
==
!=
>
<
>=
<=

TIMER
COUNTER

RISING
FALLING

STATE
GOTO
```

Then additional features can be added without changing the basic architecture.

---

# 75. Future Versions

## V1

Core PLC:

```text
Digital I/O
Variables
Boolean logic
Conditions
Timers
Counters
States
```

## V2

Industrial features:

```text
Analog I/O
Scaling
Functions
Arrays
Alarms
Faults
Persistent variables
```

## V3

Communication:

```text
Modbus RTU
Modbus TCP
RS-485
CAN
Ethernet
```

## V4

Advanced PLC features:

```text
PID
Interrupts
Tasks
Data logging
Recipes
Retentive memory
Motion control
HMI communication
```

---

# 76. Design Principle

The language should remain readable by a technician.

A machine should be understandable from the program itself.

For example:

```text
IF START AND NOT ESTOP THEN
    CONVEYOR ON
END

IF SENSOR RISING THEN
    PARTS++
END

IF PARTS >= 10 THEN
    CONVEYOR OFF
END
```

The programmer should not need to understand ESP32 GPIO registers, timers, interrupts, or memory addresses to understand the machine logic.

The ESP32 runtime handles those details underneath the language.

