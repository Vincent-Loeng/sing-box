# sing-box for FreeBSD

This self-use fork provides executable files for `386, amd64, arm, and arm64`

自用分支，提供`386、amd64、arm和arm64`等架构的可执行文件

This repo will not be updated frequently due to few modification, please add it if necessary 

由于修改很少，此仓库不会经常更新，如若需要，请手动添加


## Known issues 已知问题

None


## TO-DO 待做事项

- (**Done**) Automatically set up routing table
- `auto_redirect`



## Examples 示例

Please refer to the following template 

请参考提供的模板

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
      "fib_index": 2022, // new options 新增选项
      "auto_route": true,
      "strict_route": true,
      "endpoint_independent_nat": false,
      "stack": "system"
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
      }
    ],
    "rule_set": [],
    "auto_detect_interface": true,
    "final": "proxy"
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
