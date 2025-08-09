# Changelog

All notable changes to the Extended xv6 Operating System will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Initial implementation of hybrid SJF/RR scheduler with aging
- Demand paging and dynamic swapping system
- Complete IPC subsystem (semaphores, message queues, shared memory)
- Enhanced file system with metadata caching
- Comprehensive test programs for all features
- GitHub Actions CI/CD pipeline
- Issue templates and contribution guidelines

### Changed
- Enhanced process structure with scheduling and memory management fields
- Improved memory management with page fault handling
- Extended system call interface for IPC operations

### Fixed
- N/A (Initial release)

## [1.0.0] - 2024-08-02

### Added
- **Hybrid SJF/RR Scheduler**
  - Dynamic algorithm selection based on system state
  - Aging mechanism to prevent starvation
  - Burst time estimation using exponential averaging
  - Comprehensive scheduler statistics

- **Demand Paging System**
  - On-demand page loading
  - LRU page replacement algorithm
  - Background pager for proactive memory management
  - Swap space allocation and management
  - Page fault handling with swap-in operations

- **IPC and Synchronization**
  - System V style semaphores (semget, semop, semctl)
  - Message queues (msgget, msgsnd, msgrcv, msgctl)
  - Shared memory segments (shmget, shmat, shmdt, shmctl)
  - Proper synchronization mechanisms

- **Enhanced File System**
  - Metadata caching with LRU eviction
  - Hash table for fast inode lookups
  - Cache statistics and performance monitoring
  - Automatic cache management

- **User Test Programs**
  - `semtest`: Semaphore functionality testing
  - `schedtest`: Hybrid scheduler demonstration
  - `swaptest`: Memory management and paging testing

- **Build System**
  - Comprehensive Makefile with all dependencies
  - Support for cross-compilation
  - QEMU integration for testing

- **Documentation**
  - Detailed README with feature descriptions
  - Technical implementation details
  - Usage examples and testing instructions

### Technical Details
- **Kernel Modules**: 5 new kernel files implementing advanced features
- **Header Files**: 9 enhanced header files with new structures and definitions
- **User Programs**: 3 test programs demonstrating system capabilities
- **Build System**: Complete build infrastructure with CI/CD support

### Educational Value
- Demonstrates real-world operating system concepts
- Provides hands-on experience with advanced OS features
- Includes comprehensive testing and monitoring capabilities
- Suitable for academic and research use

---

## Version History

- **1.0.0**: Initial release with all major features implemented
- **Unreleased**: Development version with ongoing improvements

## Contributing

Please see [CONTRIBUTING.md](CONTRIBUTING.md) for details on how to contribute to this project.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
