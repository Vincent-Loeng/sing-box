# sing-box for FreeBSD

This self-use fork provides executable files for 386, amd64, arm, and arm64`

自用分支，提供`386、amd64、arm和arm64`等架构的可执行文件

This repo does not update the version frequently, please modify and compile it yourself if you need newer version

此仓库不会经常更新版本，如若需要新版本，请自行修改编译

### Another tool: [mihomo for FreeBSD](https://github.com/Vincent-Loeng/mihomo)


## Known issues 已知问题

1. `address family not supported by protocol family`


## TO-DO 待做事项

- ~~(**Done**) Automatically set up routing table~~
- (**It depends on my time**) `auto_redirect`



## Examples 示例

Please refer to the following template. When disable automatic routing, the resolv.conf would not be generated (since 1.12.0-beta.15-vincent)

请参考提供的模板，当禁用自动路由时，不生成resolv.conf（从1.12.0-beta.15-vincent起）


```json
{
  "inbounds": [
    {
      "type": "tun",
      "tag": "tun-in",
      "interface_name": "utun0",
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
      "stack": "gvisor",
      "route_address": [
        // FakeIP range
        "198.18.0.0/15",
        "fc00::/18"
        // address list that need to be proxied
        // 可在此处添加需要代理的IP地址
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
      },
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
    "auto_detect_interface": true,
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
      // To prevent "address family not supported by protocol family"
      // 避免“address family not supported by protocol family”
      {
        "action": "predefined",
        "invert": true,
        "query_type": [
          "A",
          "AAAA",
          "CNAME",
          "SRV"
        ],
        "rcode": "NOTIMP"
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


----
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
