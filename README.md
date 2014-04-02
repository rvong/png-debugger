PNGDebugger
===========
### Description
Read PNG headers, Check CRC

Tested on Windows MinGW Compiler

### Usage
pngDebugger (--verbose) file1.png file2.png file3.png ...

### Sample Run (output) on test/example.png
```
>> pngdebugger ../test/example.png
        ----
file-path=../test/example.png
file-size=183960 bytes

0x00000000      png-signature=0x89504E470D0A1A0A

0x00000008      chunk-length=0x0000000D (13)
0x0000000C      chunk-type='IHDR'
0x0000001D      crc-code=0x15141527
>> (CRC CHECK)  crc-computed=0x15141527         =>      CRC OK!


0x00000021      chunk-length=0x0002CE5F (183903)
0x00000025      chunk-type='IDAT'
0x0002CE88      crc-code=0xD16771CA
>> (CRC CHECK)  crc-computed=0xD16771CA         =>      CRC OK!


0x0002CE8C      chunk-length=0x00000000 (0)
0x0002CE90      chunk-type='IEND'
0x0002CE94      crc-code=0xAE426082
>> (CRC CHECK)  crc-computed=0xAE426082         =>      CRC OK!
```

### Sample Run (output) with --verbose flag (Detailed IHDR types)
```
>> pngdebugger --verbose ../test/example.png
        ----
file-path=../test/example.png
file-size=183960 bytes

0x00000000      png-signature=0x89504E470D0A1A0A

0x00000008      chunk-length=0x0000000D (13)
0x0000000C      chunk-type='IHDR'
0x00000010      width=0x00000320        (800)
0x00000014      height=0x00000258       (600)
0x00000018      bit-depth=8
0x00000019      color-type=2    (truecolour)
0x0000001A      compression-method=0    (deflate/inflate)
0x0000001B      filter-method=0         (adaptive)
0x0000001C      interlace-method=0      (standard)
0x0000001D      crc-code=0x15141527
>> (CRC CHECK)  crc-computed=0x15141527         =>      CRC OK!


0x00000021      chunk-length=0x0002CE5F (183903)
0x00000025      chunk-type='IDAT'
0x0002CE88      crc-code=0xD16771CA
>> (CRC CHECK)  crc-computed=0xD16771CA         =>      CRC OK!


0x0002CE8C      chunk-length=0x00000000 (0)
0x0002CE90      chunk-type='IEND'
0x0002CE94      crc-code=0xAE426082
>> (CRC CHECK)  crc-computed=0xAE426082         =>      CRC OK!
```

