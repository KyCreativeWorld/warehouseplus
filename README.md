# WarehousePlus

## What is WarehousePlus?

WarehousePlus is a warehouse database simulator using real IKEA data. It reads this data from a file, putting the data into a sorted list. Then, the user can activate an Inbound and Outbound Shipping Simulator that adds and removes items from the warehouse database.

## AI Use

During the development of this project, AI chatbots were used as a tutor/bug-tester. When hard to diagnose issues popped up, LLMs were extremely useful in finding problems and testing solutions. Using AI in this way taught me how to fix a bunch of issues and how to find bugs in my code.

## Benchmarking

| n | Create/Read | Update | Delete | Bulk Sort |
|---|---|---|---|---|
| 1,000   | 3,350 μs | 39 μs | 17 μs | 78 μs |
| 10,000  | 17,696 μs| 266 μs| 180 μs| 1,282 μs|
| 100,000 | 119,635 μs| 1,735 μs| 874 μs| 13,387 μs|
| 400,000 | 395,695 μs| 7,059 μs| 3,660 μs| 73,334 μs|
