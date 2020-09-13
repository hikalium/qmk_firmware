# hikalium keymap

https://hackmd.io/yaqYJBuPQweVm0KapwHlzQ

```
brew tap osx-cross/avr
brew install avr-gcc
brew install teensy_loader_cli
```

```
make ergodox_ez:hikalium_glow
teensy_loader_cli -mmcu=atmega32u4 -w .build/ergodox_ez_hikalium_glow.hex
```
