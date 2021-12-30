# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

Types of changes

- *Added* for new features.
- *Changed* for changes in existing functionality.
- *Deprecated* for soon-to-be removed features.
- *Removed* for now removed features.
- *Fixed* for any bug fixes.
- *Security* in case of vulnerabilities.

## [Unreleased]

## Added

- CMake build system.
  - CPack for packaging.
  - CTest for unit testing
- Unit tests
- LICENSE.txt and associated SPDX IDs, etc.
- CHANGELOG.md

## Changed

- README is now README.md.

## Removed

- Premake4 build system.

## [1.x] - 2010 to 2011 development

### Added

- Premake4 build system
  - Use --with-lua=own to check Deps/lua for user provided sources.
  - Use --with-lua=system to use the operating system's version.
  - Generate Engine.tpp for older compilers.
- Basic Manager -> per language Engine plugin concept.
- CluaEngine for Lua 5.1 support.
  - Stable, primary focus.
  - Unix and Windows.
- CpythonEngine for Python 2.x support.
  - Buggy, experimental work in progress.
  - Unix only.
