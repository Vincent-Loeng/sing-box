
**This repo may not be maintained anymore. The tool is enough to speed up some websites, e.g., OpenAI**

精力有限，可能不再维护，目前足以加速某些网站，比如 OpenAI

**Currently, only release versions are supported**

目前，仅更新 release 版

---

# sing-box for FreeBSD/OpenBSD (with tun support)
![build workflow](https://github.com/Vincent-Loeng/sing-box/actions/workflows/run.yml/badge.svg) ![build reF1nd workflow](https://github.com/Vincent-Loeng/sing-box/actions/workflows/run-reF1nd.yml/badge.svg)

This self-use repo automatically builds the latest version of sing-box with patches

此自用仓库自动应用补丁并构建 sing-box 最新的版本


## Another tool 另一工具 [**mihomo for FreeBSD**](https://github.com/Vincent-Loeng/mihomo)


## Enhancements 增强功能

1. Tun interface is supported on FreeBSD/OpenBSD

   在 FreeBSD/OpenBSD 平台上支持 Tun 网卡

2. Matching process is supported on FreeBSD since 1.12.0-beta.15-vincent-2

   自 1.12.0-beta.15-vincent-2 起，在 FreeBSD 平台上支持进程匹配

3. Redirect is supported on FreeBSD/OpenBSD since 1.12.0-beta.20-vincent-auto

   自 1.12.0-beta.20-vincent-auto 起，在 FreeBSD/OpenBSD 平台上支持 redirect

4. Subscription is supported on `reF1nd` core, please refer to [the document](https://github.com/reF1nd/sing-box/blob/reF1nd-main/docs/configuration/provider/index.md)

   `reF1nd`核心支持订阅，请参考[文档](https://github.com/reF1nd/sing-box/blob/reF1nd-main/docs/configuration/provider/index.zh.md)，第三方核心的订阅功能较为相似，使用上区别小，选此核心仅为尽量满足订阅外的其他需求



## Examples 示例

Please refer to the given [template](template.json) (1.12)

请参考提供的[模板](template.json)（1.12）


## Known issues 已知问题

1. Loops may happen on OpenBSD, the workround is shown in the template

   OpenBSD上可能出现环路，绕过方法在模板里



## TO-DO 待做事项

1. Utilize `sendmmsg/recvmmsg` to improve tun performance

   使用 `sendmmsg/recvmmsg` 提升 tun 性能

2. Automatic redirect


## Notes 注意事项


1. Please configure DNS servers manually when using automatic routing on OPNsense

   在 OPNsense 上使用自动路由时，请手动配置 DNS 服务器

2. Please allow packets to pass when using `system` stack on pfSense/OPNsense

   在 pfSense/OPNsense 上使用`system`栈时，请允许数据包通过

3. Please add port forwarding rules when using `redirect` (higher performance)

   使用 `redirect`（性能更好）时，请添加端口转发规则

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
