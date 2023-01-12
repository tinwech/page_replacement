# Page replacement

This repository implements LRU and LFU for page replacement.

## Description

Page replacement is a technique used in computer systems to manage the use of memory. When the system runs out of physical memory, it must choose which pages of memory to keep in physical memory and which to remove (replace) in order to make room for new pages. Here, we introduce two page replacement algorithms:

### LRU

The LRU algorithm replaces the page that has not been accessed for the longest time. It is based on the idea that pages that have not been accessed in a long time are unlikely to be accessed in the future. LRU is easy to implement and can quickly adapt to change of working set; however, it can suffer from cache pollution, since it allows recently used page to be swapped in, pushing out of the cache information that will be used again soon.

![image](https://user-images.githubusercontent.com/80531783/212017052-48acfe5b-5a84-4153-96fa-096b90ab9b84.png)


### LFU

The LFU algorithm replaces the page that has been accessed the least number of times. It is based on the idea that pages that have been accessed less frequently are less important and can be replaced. It is more complex to implement LFU and has higher overhead, but it solves the cache pollution problem of LRU.

## Getting started

```shell
make
./main whois.txt
./main zipf.txt
```

### Result

#### whois.txt

![image](https://user-images.githubusercontent.com/80531783/212014927-06ae9864-68e4-4401-9625-4cd452bcc916.png)

#### zipf.txt

![image](https://user-images.githubusercontent.com/80531783/212015081-c539a95d-4a63-47ea-bdbe-3a173cd2cdd8.png)
