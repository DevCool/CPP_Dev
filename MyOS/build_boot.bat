@echo off



nasm -f bin boot.asm -o boot.bin

dd if=boot.bin of=\\?\Device\Floppy0 bs=512 count=1 skip=0

del boot.bin



pause

exit