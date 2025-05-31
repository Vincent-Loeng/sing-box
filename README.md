
**This repo may not be maintained anymore. The tool is enough to speed up some websites, e.g., OpenAI**

精力有限，可能不再维护，目前足以加速某些网站，比如 OpenAI

---

# sing-box for FreeBSD/OpenBSD (with tun support)

This self-use fork provides executable files for _**386, amd64, arm, and arm64**_

自用分支，提供 _**386、amd64、arm和arm64**_ 等架构的可执行文件

This repo automatically builds the latest FreeBSD version of sing-box with patches, and the latest OpenBSD version is [1.12.0-beta.19-vincent-1](https://github.com/Vincent-Loeng/sing-box/releases/tag/1.12.0-beta.19-vincent-1)

此仓库自动应用补丁并构建最新的 sing-box FreeBSD 版本，另外，最新的 OpenBSD 版本是 [1.12.0-beta.19-vincent-1](https://github.com/Vincent-Loeng/sing-box/releases/tag/1.12.0-beta.19-vincent-1)

## Another tool 另一工具 [**mihomo for FreeBSD**](https://github.com/Vincent-Loeng/mihomo)


## Enhancements 增强功能

1. Tun interface Tun网卡

2. Matching process is supported in FreeBSD since 1.12.0-beta.15-vincent-2

   自 1.12.0-beta.15-vincent-2 起，FreeBSD 平台支持匹配进程

3. Redirect (IPFW) is supported in FreeBSD since 1.12.0-beta.20-vincent-auto

   自 1.12.0-beta.20-vincent-auto 起，FreeBSD 平台支持 Redirect (IPFW)


## TO-DO 待做事项

1. (**It depends on my time**) `set_system_proxy`

2. (**It depends on my time**) `auto_redirect`


## Known issues 已知问题

1. Loops may happen on OpenBSD    可能出现环路


## Notes 注意事项

1. The value of `auto_detect_interface` should be `false` since 1.12.0-beta.15-vincent-2, which does not affect tun interfaces

   自 1.12.0-beta.15-vincent-2 起，`auto_detect_interface`的值应该设为`false`，不影响 tun 网卡

3. Please use `FakeIP` to avoid loops when using OpenBSD

   使用 OpenBSD 时，请用`FakeIP`避免环路


## Examples 示例

Please refer to the given [template](template.json) (1.12)

请参考提供的[模板](template.json)（1.12）

---

# sing-box

The universal proxy platform.

[![Packaging status](https://repology.org/badge/vertical-allrepos/sing-box.svg)](https://repology.org/project/sing-box/versions)

## Documentation

https://sing-box.sagernet.org

## License

```
Copyright (C) 2022 by nekohasekai <contact-sagernet@sekai.icu>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

In addition, no derivative work may use the name or imply association
with this application without prior consent.
```
