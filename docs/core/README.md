# R8GE Core module

Core module is the base of the engine.

## Features

### Logging

- For logging into `stdout`, there is created `mainLogger`, you may access it with pointer (`global::logger`). Object is also accessed by macros.
  - `R8GE_LOG_INFOR`, `R8GE_LOG_WARN`, `R8GE_LOG_ERROR`, `R8GE_LOG_FATAL`, `R8GE_LOG_DEBUG`, `R8GE_LOG_TRACE`, `R8GE_LOG` (`R8GE_LOG_TRACE`)

- For filtering log levels you shall use:
  ``` cpp
  r8ge::global::logger->setMinLevel(r8ge::Logger::Priority::INFOR);
  ```
  - Any log level below `INFOR` will be ignored.
- For viewing specific logs, you may use:
  ``` cpp
    r8ge::global::logger->setLevels({
      r8ge::Logger::Priority::INFOR,
      r8ge::Logger::Priority::ERROR,
      r8ge::Logger::Priority::FATAL
    });
  ```
  - This will only show `INFOR`, `ERROR` and `FATAL` logs. 
  > Min level is not forgotten after setting levels, so if you set levels and then set min level, it will be ignored; you should reset min-log level to trace.
  
- Logger uses `r8ge::utility::StringFormat()` class for formatting strings, so you may use it for your own purposes.
  - `r8ge::utility::StringFormat()` is a similar to fmt library.
  - You may use it like this:
    ``` cpp
    R8GE_LOG("Hello, {}!", "World"); // World!
    R8GE_LOG("Hello, {0}! {0}!", "World"); //Hello, World! World!
    R8GE_LOG("Hello, {1}! {0}!", "World", "How are you?"); // Hello, How are you?! World!
    R8GE_LOG("[]()\\{0}{0}", "{}"); // [](){0}{}
    R8GE_LOG("Wrong element: {0} {1}", "Hello"); // Wrong element: Hello {missing_value}
    // Empty braces are evaluated separately
    //             0  1      2  2   - Number will not exceed element list
    R8GE_LOG("{0} {} {} {1} {} {}", "Ahoj", 1, 2); // Ahoj Ahoj 1 1 2 2
    ```
- Logger also supports custom formatting styles.
  - You may use it like this:
    ``` cpp
    r8ge::global::logger->setFormat("Hello, {0}! {1}!");
    ```
  - `%%` - outputs `%`
  - `%H` - Hours <0;24)
  - `%M` - Minutes <0;60)
  - `%S` - Seconds <0;60)
  - `%m` - Milliseconds <0;1000)
  - `%u` - Microseconds <0;1000)
  - `%n` - Nanoseconds <0;1000)
  - `%X` - %H:%M:%S
  - `%^` - %m:%u:%n
  - `%l` - log message
  - `%L` - log level ("trace", "debug", "infor", ""error", "warni", "fatal")
  - ~~`%o` - originated from ("engine", "client", "server", "unknown")~~
  - ~~`%t` - thread id~~
  - `%U` - All next characters will be uppercase
  - `%D` - All next characters will be lowercase
  - `%<` - All next characters will be default case
  - `%C` - Set to specified log level color
  - `%c` - Reset colors
  - For output styles:
    - Styled  - S
    - Default - D
  ``` cpp
  // [/-----> /------> /-------> /------> /------>
  // |Default| Styled  | Default | Styled | Default
  //"[data] %C [data] %c [data] %C" ... "%c"
  ```
 
### File I/O
  ``` cpp 
    r8ge::File<Readers::[reader]>(path: string)
  ```
  - `load()` - Loads file into memory from disk
  - `save()` - Saves file from memory to disk 

### Instance
#### Game instance
- Class that is used for running the game
- After creating instance class, that inherits from `r8ge::GameInstance` you shall override all its methods.
- TODO