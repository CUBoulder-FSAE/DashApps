# DashApps
CAN, Logging, and UI Apps for the DASH

## Setting up the Repo

Make sure the DashBuildroot repo is cloned at the same directory level as DashApps

For example I have \
~/stuff/DashApp \
~/stuff/DashBuildroot

This is important because DashApp looks over to DashBuildroot for the Software Development Kit (SDK).

The SDK contains the .h files and libraries needed to build applications that will run on the dash.

## Building an app

### Prereqs
Make sure to build the SDK in the DashBuildroot repo. Go to that repo's README for instructions on how to do that. Once that is done we can proceed to the next step.

### Building time :)

#### Source the sdk
Source the environment variables so that the SDK is used when compiling our programs. You need to run this everytime you create a new terminal instance.

```bash
source scripts/env
```

Note: If you get a message like this you either need to build the SDK or the DashBuildroot directory is not on the same directory level:
```
scripts/env:source:5: no such file or directory: /home/dylan/stuff/DashApps/../DashBuildroot/buildroot/output/host/environment-setup
```

#### Initialize CMake
Now initialize the CMake. You need to run this command when you first clone the repo or when you make changes to a CMakeLists.txt file (adding libraries or adding a source file)

```bash
cmake -B build
```

#### Build Command
Now run this command when you want to build an application. This will build all applications.
```bash
make -C build
```

#### Building a specific application
If you just want to build a specific application, run this
```bash
make -C build <Application Name>

# Build the CAN application
make -C build CAN
```

### Generated Application
The built application will be
```bash
<currentdir>/build/<App Name>/<App Name>

# UI generated application
<currentdir>/build/UI/UI
```







