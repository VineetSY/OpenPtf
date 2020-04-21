# OpenPtf Project book

## Peripherals Enabled

### 1. Clock Enabled
```

    - HSI 16MHZ
    - MSI 48MHZ
    - PLL 80MHZ (From MSI 48)
```

### 2. GPIO Enabled
```
    - PORTA Pin5 output mode(Nucleo-L476 on board LED)
    - PORTA Pin5 output mode(External LED)
```

### 3.Timer Enabled
```
    - TIM2 as ReloadTimer (DownCount Autoreload with Interrupt at underflow)
```

## Modules

### 1. CLOCK
```
    - Handling of all Clock configuration and Peripheral clock enable.
```

### 2. GPIO
```
    - Configuration of all GPIO pins and PORT modes.
```

### 3. TIMER
```
    - Handling of all Timer functionality including SysTick.
```