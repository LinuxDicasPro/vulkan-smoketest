<p align="center">
  <img src="logo.png" width="256">
</p>

<h1 align="center">Vulkan Smoke Test</h1> 

<h3 align="center">This is a simple smoke test utility to verify that the Vulkan environment is 
correctly installed and functional on your system.
<br/><br/>
The project was originally maintained within the Vulkan-Tools repository until 
version 1.1.70, when it was removed. This repository aims to preserve and maintain 
vulkan-smoketest independently.</h3>

## 🎯 Objective

vulkan-smoketest is a minimalist and essential diagnostic tool that initializes a
Vulkan instance, checks crucial surface extensions, and attempts to create a
logical device.

Its primary purpose is to confirm the integrity of your Vulkan stack, being
useful in scenarios such as:

* Post-installation validation of drivers and SDK.
* Diagnosis in Linux distributions or live environments.
* Confirming the Vulkan stack is functional.

## 🧩 Compatibility

* ✅ Tested with Vulkan SDK **1.2.176.1**
* 🔄 Compatible with Vulkan SDK **1.0+**
* 🧰 Compilers: **GCC**, **Clang**, **MSVC**

## 🚀 Key Adjustments

### Wayland Modernization and Stability

This version introduces modern support for the Wayland/XDG Shell protocol
and includes crucial stability enhancements for Vulkan window operation,
along with **zxdg_decoration_manager_v1** for native window decorations
(Server-Side Decorations - SSD).

### Critical Stability Fix

This version implements a solution for the recurring bug error
**VK_ERROR_NATIVE_WINDOW_IN_USE_KHR (VkResult 1000001003)**, which was
triggered when trying to resize or maximize and restore the window.

## 🛠️ Compilation

### Requirements

* Vulkan SDK installed (or Vulkan headers and loader available on the system)
* CMake
* For Wayland: Wayland client headers and libraries (and **wayland-scanner**)

### Build Instructions

```bash
git clone https://github.com/seu-usuario/vulkan-smoketest.git
cd vulkan-smoketest
mkdir build && cd build

# Standard build (detects the best option for the platform)
cmake ..
make

# --- OR ---

# Forced build for Wayland/XDG (required if you want to test the Wayland backend)
cmake .. -DBUILD_SELECTION=WAYLAND
make
```

## ▶️ Usage

After compilation:

```bash
./vulkan-smoketest
```

Or if compiled with Wayland:

```bash
./vulkan-smoketest-wayland
```

### Expected Output

A list of basic Vulkan instance information and the result of logical device creation.

```text
Detected GPUs:
        - Intel(R) UHD Graphics 620 (WHL GT2)      (Type: Integrated)
        - llvmpipe (LLVM 13.0.0, 256 bits)         (Type: Other)
        - NVIDIA GeForce MX110                     (Type: Dedicated)
Selected GPU for test: Intel(R) UHD Graphics 620 (WHL GT2)
  840 presents in 5.0039  seconds (FPS: 167.869)
  810 presents in 5.00021 seconds (FPS: 161.993)
 1073 presents in 5.00398 seconds (FPS: 214.429)
 1149 presents in 5.00368 seconds (FPS: 229.631)
frames:4058, elapses:21011
```

## 📜 License

This project is licensed under the **Apache License 2.0**. 🧾

## 🕰️ History

* 📌 Originally part of **KhronosGroup/Vulkan-Tools**
* ❌ Removed after version **1.1.70**
* ♻️ Project rescued and maintained independently by **LinuxDicasPro**

## 🤝 Contributions

Contributions are actively encouraged! To ensure vulkan-smoketest remains
a relevant diagnostic tool, we seek collaboration from the community.

### Main Focus for Contributions

* **Platform Stability**: Testing and fixing backend-specific bugs.
* **SDK Compatibility**: Maintaining compliance with new Vulkan SDK versions
and specifications.
* **Diagnostic Improvement**: Adding more integrity checks and providing more
detailed and useful error logs.

To contribute, please create an **Issue** or submit a **Pull Request**.
