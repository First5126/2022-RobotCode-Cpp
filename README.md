# 2022 ROBOT C++

This is the 2022 c++ robot code for the **Rapid React** game. 

This program
implements all parts of a functioning robot in a style called 
`command structure`. 
`command structure` is a style of FRC programming that involves 'commands'
 for each thing on the robot. Each `command` will take a `subsystem` to control.

A subsystem is a abstraction of the hardware on the robot. For example a common 
`subsystem` might be an 'intake'. A common thing that intakes might need to do
is `run()`, `stop()`, `toggle()`! This subsystem handles everything that we
might want to do with this thing on the robot. A `command` is something that 
takes that a step further. Something we might want to do with an intake command
is that we might want it to `intake_ball()` or maybe `deploy()`.   

### How Command Structure Works
---
```c++
/**
 * An example command that uses an example subsystem.
 *
 * <p>Note that this extends CommandHelper, rather extending CommandBase
 * directly; this is crucially important, or else the decorator functions in
 * Command will *not* work!
 */
class ExampleCommand
    : public frc2::CommandHelper<frc2::CommandBase, ExampleCommand> {
 public:

  /**
   * Creates a new ExampleCommand.
   *
   * @param subsystem The subsystem used by this command.
   */

  explicit ExampleCommand(ExampleSubsystem* subsystem);

  // Called when the command is init
  void Initialize() override;

  // Runs every tick untill the command ends
  void Execute() override;

  // Tells that the command is done
  bool IsFinished() override;

  // Runs when the command stops
  void End(bool interrupt) override;


 private:

  // Var storage
  ExampleSubsystem* m_subsystem;
};


```



This is an example command. This command has several methods that are called at 
different times during its execution. The `Initialize()` function is called when
the command begins, this might be used to reset the state of common subsystems
or maybe reset `PIDControllers`.

The `Execute()` method is called every robot packet untill the command is 
stopped. This is where the main part of the commands code should be. This will 
handle changing or waiting on states of `subsystems`.

Lastly we have the `IsFinished()` and `End(bool)` methods. The `IsFinished()` 
method is called also every robot packet, but instead of running code, this
method should be used to tell if the command has finished or not. Finally we 
have the `End()` method. This method is just like the `Initialize()` method,
as it is called when the command is finished. 

## How the Robot code is Structured
---

There are many subsystems that make up a production robot. On our robot we have
the following:

### Subsystems
- Drive Train
- Intake
- Shooter
- Climer
- Vision

Each one of these is important for the robot to function and all of these serve
an important function. Without the `Drive Train` we would not be able move, and
without `Shooter` we would not be able to score. It is important that our 
subsystems be programmed with care and functionality in mind. 

***--- NO INSTANCE VARIABLES SHOULD BE PUBLIC---***

**All control should be a method!**

Now we also have `commands` that sit ontop of that. Some basic commands are
as follows:

### Commands
- Turn Degrees
- Drive Distance
- Shoot Power
- Intake Toggle


These comands control and abstract the structure of the robot. For example the 
`ShooterCommand` might take do a multiple things. Some of the things it needs to
do is as follows.

```c++
/* 1. Spin up shooter
 * 2. Wait until the shooter is up to speed
 * 3. Release ball into shooter
 * 4. Reset the shooter / Hood
 * 5. End
*/
```

This would be too much for us to want to do without commands, so we can put it 
into a `command`. 













