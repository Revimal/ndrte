# ndrte

<img src="https://avatars3.githubusercontent.com/u/19686401" align="center" />

'ndrte' is a light-weight parallel computing framework, that is focusing on fast packet processing.
It is designed to provide network developers an easy, efficient, and flexible way to create software products which need to send, receive and manipulate network packets.
It runs mostly in linux userland; process task scheduling and memory mapping autonomously to achieve the best performance and low-latency.

*It's inspired by [Intel® Data Plane Development Kit](http://dpdk.org/)*

[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
[![License: GPL-3.0 (Linux kernel modules)](https://img.shields.io/badge/License-GPL--3.0-green.svg)](https://opensource.org/licenses/GPL-3.0)
[![Release: 1.0.0-rc1](https://img.shields.io/badge/release-v1.0.0--rc1-blue.svg)](https://github.com/openndr/ndrte/releases/tag/v1.0.0-rc1)
[![Build Status](https://travis-ci.org/openndr/ndrte.svg?branch=master)](https://travis-ci.org/openndr/ndrte)
[![codecov](https://codecov.io/gh/openndr/ndrte/branch/master/graph/badge.svg)](https://codecov.io/gh/openndr/ndrte)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6fcd0e75a03d4eeaace932209af682f0)](https://www.codacy.com/app/Revimal/ndrte?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=openndr/ndrte&amp;utm_campaign=Badge_Grade)
[![Coverity Status](https://img.shields.io/coverity/scan/15327.svg)](https://scan.coverity.com/projects/openndr-ndrte)

## Latest Release
### 1.0.0-rc1
- [Release](https://github.com/openndr/ndrte/releases/tag/v1.0.0-rc1)
- [Change Log]()

## Features
### Light-weight context switching scheduler
* Coroutine like light-weight work unit [indev]

### Packet user-space mapping drivers
* 1-copy skbuff user-mapping (for generic drivers) [indev]
* 0-copy skbuff user-mapping (for ixgbe) [indev]

## Documentation
Reference [here](https://github.com/openndr/ndrte/wiki)
