# sing-box for FreeBSD

This self-use fork provides executable files for `386, amd64, arm, and arm64`

自用分支，提供`386、amd64、arm、arm64`等架构的可执行文件


## Known issues 已知问题

Due to the limitaion of FreeBSD route api, traffic Loops may happen when using `auto_route`, please refer to the given examples

由于 FreeBSD route api 的限制，使用`auto_route`时可能触发环路，请参考以下示例


## Examples 示例

### 1. FakeIP

Please refer to the following template to avoid traffic loops 

请参考提供的模板，以避免环路问题

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
      "auto_route": true,
      "strict_route": true,
      "endpoint_independent_nat": false,
      "stack": "system",
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
        "invert": true,
        "rule_set": [],
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

### 2. FIB (without automatic routing)

```bash
## 1. add the follwing parameters to /etc/sysctl.conf and reboot
## 1、添加以下参数到/etc/sysctl.conf并重启
net.fibs=2
net.add_addr_allfibs=1

## 2. add routing rules manually
## 2、手动添加路由规则
setfib 1 route add default <gateway>
setfib 1 route add -inet6 default <gateway6>
setfib 1 <path>/sing-box -c <path>/config.json run
route add -net 1.0.0.0/8 <tun_gateway>
route add -net 2.0.0.0/7 <tun_gateway>
route add -net 4.0.0.0/6 <tun_gateway>
route add -net 8.0.0.0/5 <tun_gateway>
route add -net 16.0.0.0/4 <tun_gateway>
route add -net 32.0.0.0/3 <tun_gateway>
route add -net 64.0.0.0/2 <tun_gateway>
route add -net 128.0.0.0/1 <tun_gateway>
route add -net 198.18.0.0/15 <tun_gateway6>
route add -net -inet6 100::/8 <tun_gateway6>
route add -net -inet6 200::/7 <tun_gateway6>
route add -net -inet6 400::/6 <tun_gateway6>
route add -net -inet6 1000::/4 <tun_gateway6>
route add -net -inet6 2000::/3 <tun_gateway6>
route add -net -inet6 4000::/2 <tun_gateway6>
route add -net -inet6 8000::/1 <tun_gateway6>
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
