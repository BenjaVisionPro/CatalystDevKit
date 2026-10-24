# Introduction to Catalyst

A multiuser system needs to run application code, preserve information, and coordinate changes made by different users. An order must survive a restart. Two customers cannot both buy the last ticket. A transfer must debit one account and credit another as one operation.

Every running application uses memory, but RAM is finite and temporary. You have probably addressed this by adding a database. Then you write code to move data into memory for your application to use, and write it back to the database when things change. Schemas, queries and adapters connect the two, often requiring different languages, tools and skills.

**GemStone removes this translation layer by making application object memory persistent.**

Objects, their relationships, and the Smalltalk classes and methods that define their behaviour live in one persistent environment. You work directly with the objects your application models, without maintaining a separate database representation. [GemStone overview](https://downloads.gemtalksystems.com/docs/GemStone64/3.7.x/GS64-ProgGuide-3.7/1-IntroToGemStone.htm)

That persistent world lives on disk and can grow far beyond available RAM. GemStone caches the portions currently needed. When your application references an object or calls a method that is not in memory, GemStone loads it automatically and execution continues—without application code to manage that loading. [Memory management](https://gemtalksystems.com/techsupport/techtip-diagnosing-out-of-memory-errors/)

Many processes across multiple physical machines can access the same persistent object world. Each session works with a consistent view, and related changes can be committed transactionally. GemStone coordinates commits and detects conflicting updates. [Transactions and concurrency](https://downloads.gemtalksystems.com/docs/GemStone64/3.7.x/GS64-ProgGuide-3.7/9-Transactions.htm)

**Catalyst builds on GemStone with a framework for application execution, services, client connections and development tools.**

You define your application's objects and rules. GemStone provides persistence and coordinated access; Catalyst provides the framework around them. Fewer representations and fewer adapters mean less infrastructure to maintain—and more time to build your application.
