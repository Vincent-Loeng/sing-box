
**This repo may not be maintained anymore. The tool is enough to speed up some websites, e.g., OpenAI**

精力有限，可能不再维护和发布，目前足以加速某些网站，比如 OpenAI

---

# **sing-box for FreeBSD/OpenBSD**

This self-use fork provides executable files for _**386, amd64, arm, and arm64**_

自用分支，提供 _**386、amd64、arm和arm64**_ 等架构的可执行文件


## Another tool 另一工具 [**mihomo for FreeBSD**](https://github.com/Vincent-Loeng/mihomo)


## Known issues 已知问题

1. Loops may happen in OpenBSD

   OpenBSD 平台可能出现环路


## TO-DO 待做事项

1. (**It depends on my time**) `set_system_proxy`

2. (**It depends on my time**) `auto_redirect`


## Notes 注意事项

1. This repo does not update version frequently, please modify and compile it yourself if you need newer version

   此仓库不会经常更新版本，如若需要新版本，请自行修改编译

2. When automatic routing is enabled, this tool would handle the contents of /etc/resolv.conf

   启用自动路由时，此工具将处理 resolv.conf 中的内容

3. To be consistent with the official repo, the value of `auto_detect_interface` should be `false` since 1.12.0-beta.15-vincent-2, which does not affect tun interfaces

   与原版仓库保持一致，自 1.12.0-beta.15-vincent-2 起，`auto_detect_interface`的值应该设为`false`，不影响 tun 网卡

4. Please use `FakeIP` and `ignore dns` (an option in dhcpleased.conf) when using OpenBSD

   使用 OpenBSD 时，请用`FakeIP`和 `ignore dns` (dhcpleased.conf 中的一个选项) 


## Examples 示例

Please refer to the following template (1.12)

请参考提供的模板（1.12）

```json
{
  "inbounds": [
    {
      "type": "tun",
      "tag": "tun-in",
      "interface_name": "tun0",
      "address": [
        "172.19.0.0/30",
        "fdfe:dcba:9876::0/126"
      ],
      "mtu": 9000,
      // new option, default value is 2022
      // 新增选项，默认值是2022
      "fib_index": 2022,
      // enable automatic routing
      // 启用自动路由
      "auto_route": true,
      "strict_route": true,
      "endpoint_independent_nat": false,
      "stack": "system",
      // Use custom routes instead of default when auto_route is enabled.
      // 自定义路由
      "route_address": [
        // FakeIP ranges
        "198.18.0.0/15",
        "fc00::/18"
        // addresses that need to be proxied
        // 可在此处添加需要代理的地址
      ]
    }
  ],
  "outbounds": [
    {
      "tag": "proxy",
      "type": "shadowsocks",
      "server": "",
      "server_port": 12345,
      "method": "",
      "password": ""
    }
  ],
  // add proxy rules as needed
  // 可按需添加规则
  "route": {
    "default_domain_resolver": {
      "server": "local-dns"
    },
    "rules": [
      {
        "action": "sniff",
        "inbound": "tun-in",
        "sniffer": [
          "dns",
          "http",
          "tls",
          "quic"
        ]
      },
      {
        "action": "hijack-dns",
        "type": "logical",
        "mode": "or",
        "rules": [
          {
            "port": 53
          },
          {
            "protocol": "dns"
          }
        ]
      },
      {
        "action": "route",
        "ip_is_private": true,
        "outbound": "direct"
      },
      {
        "action": "route",
        "rule_set": "openai",
        "outbound": "proxy"
      }
    ],
    "rule_set": [
      {
        "tag": "openai",
        "type": "remote",
        "url": "https://raw.githubusercontent.com/MetaCubeX/meta-rules-dat/refs/heads/sing/geo/geosite/openai.srs",
        "format": "binary",
        "download_detour": "proxy"
      }
    ],
    "auto_detect_interface": false,
    "final": "direct"
  },
  "dns": {
    "servers": [
      {
        "tag": "local-dns",
        "type": "udp",
        "server": "223.5.5.5"
      },
      {
        "tag": "remote-dns",
        "type": "udp",
        "server": "8.8.8.8",
        "detour": "proxy"
      },
      {
        "tag": "fakeip-dns",
        "type": "fakeip",
        "inet4_range": "198.18.0.0/15",
        "inet6_range": "fc00::/18"
      }
    ],
    "rules": [
      {
        "action": "route",
        "invert": true,
        "rule_set": [
          "openai"
        ],
        "server": "local-dns"
      },
      {
        "action": "route",
        "query_type": [
          "A",
          "AAAA"
        ],
        "server": "fakeip-dns",
        "rewrite_ttl": 1
      }
    ],
    "disable_cache": false,
    "disable_expire": false,
    "independent_cache": true,
    "final": "remote-dns",
    "strategy": "prefer_ipv4"
  }
}
```


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
