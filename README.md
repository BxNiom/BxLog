# BxLog
Simple logging for C++

## Usage

### Syntax

Default usage:
```cpp
    BX_LOG( [error | warn | info | debug | verbose] ) << Message
```

Conditional logging:
```cpp
    BX_LOG_IF( [error | warn | info | debug | verbose], condition ) << Message
```

Set log level:
```cpp
    BX_LOG_LEVEL( [error | warn | info | debug | verbose] )
```

__Example__
```cpp
#include <bxlog.hpp>

int main() {
    BX_LOG(info) << "Hello from BxLog";
    bool test = true;
    BX_LOG_IF(debug, test) << "Test is true";
    return 0;
}
```

## Message format

Default message format:
```shell
"[%d %t] %lv.upper | %ti | %fi(%ln): %m"
```
Output:
```shell
[2022-04-03 17:38:23] INFO | 0x7c5e230adf | main.cpp(4) : Hello from BxLog
```

### Customisation
Message format currently only configurable in code

```cpp
#include <bxlog.hpp>

int main() {
    bxniom::log::Log::getInstance()->format("[%d %t] %lv.upper | %ti | %fi(%ln): %m");
    return 0;
}
```

### Possible format parameters<br>

| Ident      | Description                                                                                                  |
|------------|--------------------------------------------------------------------------------------------------------------|
| %d         | Date                                                                                                         |
| %d(FORMAT) | Date with custom format. See [here](https://en.cppreference.com/w/cpp/chrono/c/strftime) for format patterns |
| %t         | Time                                                                                                         |
| %t(FORMAT) | Time with custom format. See [here](https://en.cppreference.com/w/cpp/chrono/c/strftime) for format patterns |
| %lv        | Level                                                                                                        |
| %fn        | Function                                                                                                     |
| %fi        | Filename                                                                                                     |
| %ln        | Line                                                                                                         |
| %ti        | Thread ID                                                                                                    |
| %m         | Message                                                                                                      |
