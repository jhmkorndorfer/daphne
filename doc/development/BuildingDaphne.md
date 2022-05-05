# Building Daphne

The DAPHNE project provides a full-fledged build script. After cloning it does everything from dependency setup to 
generation of the executable.

### What does the build script do? (simplified)

- Download & build all code dependencies
- Build Daphne
- Clean Project

### How long does a build take?

The first run will take a while, due to long compilation times of the dependencies. But they only have to be compiled 
once (except updates).
Following builds only take a few seconds/minutes.

Contents:
 - [Usage of the build script](#1-usage-of-the-build-script)
 - [Extension of the build script](#2-extension)





--- 
## 1. Usage of the build script

This section shows the possibilities of the build script.

### Build

The default command to build the default target **daphne**.

```bash
./build.sh
```

Print the cli build help page. This also shows all of the following options.

```bash
./build.sh --help
```

Build a specific **target**.

```bash
./build.sh --target "target"
```
For example the following builds the main test target.
```bash
./build.sh --target "run_tests"
```


### Clean

Clean all build directories, i.e. the daphne build dir in `<project_root>/build` and build directories of the dependencies in 
`<project_root>/thirdparty/<dep>/<path to build folder>`:

```bash
./build.sh --clean
```

Clean all download and build directories, i.e. `<project_root>/build` and `<project_root>/thirdparty/*`

```bash
./build.sh --cleanAll
```
### Options
All possible options for the build script:

| Option             | Effect |
|--------------------| ------- |
| -h, --help         | Print the help page |
| --clean            | Clean build directories |
| --cleanAll         | Clean build directory and delete all dependency |
| --target \<target> | Build specific target |
| -nf, --no-fancy    | Disables colorized output |
| -y, --yes          | Accept prompt (e.g. when executing the clean command) |


## 2. Extension
### Overview over the build script
The build script is divided into segments, visualized by
```
#******************************************************************************
# Segment name
#******************************************************************************
```
Each segment should only contain functionality, related to the segment name.

The following list contains a rough overview over the segments and the concrete functions or functionality done here. 
1. Help message
   1. **printHelp()** // prints help message
2. Build message helper
   1. **daphne_msg(** [-t \<timeframe>] \<message> **)** // prints a status message in DAPHNE style; optional timeframe for animated output
   2. **printableTimestamp(** \<timestamp> **)** // converts a unix epoch timestamp into a human readable string (e.g. 5min 20s 100ms)
   3. **printLogo(** [-t \<timeframe>]**)** // prints a DAPHNE logo to the console
3. Clean build directories
   1. **clean(** \<array ref dirs> \<array ref files> **)** // removes all given directories (1. parameter) and all given files (2. parameter) from disk
   2. **cleanBuildDirs()** // cleans build dirs (daphne and dependency build dirs)
   3. **cleanAll()** // cleans daphne build dir and wipes all dependencies from disk 
4. Create / Check Indicator-files
   1. **dependency_install_success(** \<dep> **)** // used after successful build of a dependency; creates related indicator file 
   2. **dependency_download_success(** \<dep> **)** // used after successful download of a dependency; creates related indicator file
   3. **is_dependency_installed(** \<dep> **)** // checks if dependency is already installed/build successfully  
   4. **is_dependency_downloaded(** \<dep> **)** // checks if dependency is already downloaded successfully
5. Set some paths
   1. Definition of project related paths
6. Parse arguments
   1. Parsing
   2. Updating git submodules
7. Download and install third-party material if necessary
   1. Antlr
   2. catch2
   3. OpenBLAS
   4. gRPC
   5. MLIR
8. Build DAPHNE target
   1. Compilation of the DAPHNE-target ('daphne' is default)

### Adding a dependency
1. Create a new subsegment in segment 7.
2. Define needed dependency variables
   1. DirName
   2. Version
   3. Dep-specific paths
   4. Dep-specific files
   5. etc.
3. Download the dependency, encased by:
    ```
   dep_dirname="<dep_name>"
   dep_version="<dep_version>"
    if ! is_dependency_downloaded "<dep_name>_v${dep_version}"; then
   
        # do your stuff here
   
        dependency_download_success "<dep_name>_v${dep_version}"
    fi
    ```
4. Install the dependency (if necessary), encased by:
    ```
    if ! is_dependency_installed "<dep_name>_v${dep_version}"; then
   
        # do your stuff here
   
        dependency_install_success "<dep_name>_v${dep_version}"
    fi
    ```