# 华宝证券行情接收机

特点
---
采用 mmap 实现了 lock-free 的并行写入，非常迅速，但是需要足够的内存<br/>
为避免 remap， 最初分配 20 GB 左右内存为佳，可以在 config.ini 修改，单位为 GB

Usage
---
修改 config.ini 按照实际配置

make 后运行
