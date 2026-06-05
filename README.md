# WarehousePlus

## What is WarehousePlus?

WarehousePlus is a warehouse database simulator using real IKEA data. It reads this data from a file, putting the data into a sorted list. Then, the user can activate an Inbound and Outbound Shipping Simulator that adds and removes items from the warehouse database.

## AI Use

During the development of this project, AI chatbots were used as a tutor/bug-tester. When hard to diagnose issues popped up, LLMs were extremely useful in finding problems and testing solutions. Using AI in this way taught me how to fix a bunch of issues and how to find bugs in my code.

## Benchmarking

``` cpp
    n         | Create/Read | Update | Delete | Bulk Sort | Time is in ms
    1,000     |
    10,000    |
    100,000   |
```