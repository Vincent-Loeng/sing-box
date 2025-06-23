## apply patches
cd ../sing-tun
# freebsd
cp monitor_darwin.go monitor_freebsd.go
cp tun_darwin_gvisor.go tun_freebsd_gvisor.go
sed -i 's|DarwinEndpoint|FreeBSDEndpoint|g;s|darwin|freebsd|g' tun_freebsd_gvisor.go
# openbsd
cp monitor_darwin.go monitor_openbsd.go
cp tun_darwin_gvisor.go tun_openbsd_gvisor.go
sed -i 's|DarwinEndpoint|OpenBSDEndpoint|g;s|darwin|openbsd|g' tun_openbsd_gvisor.go
# dragonfly
#cp monitor_darwin.go monitor_dragonfly.go
#cp tun_darwin_gvisor.go tun_dragonfly_gvisor.go
#sed -i 's|DarwinEndpoint|DragonFlyEndpoint|g;s|darwin|dragonfly|g' tun_dragonfly_gvisor.go
git diff HEAD > ../sing-box/sing-tun.patch

cd ../sing-tun-meta
# freebsd
cp monitor_darwin.go monitor_freebsd.go
cp tun_darwin_gvisor.go tun_freebsd_gvisor.go
sed -i 's|DarwinEndpoint|FreeBSDEndpoint|g;s|darwin|freebsd|g' tun_freebsd_gvisor.go
# dragonfly
#cp monitor_darwin.go monitor_dragonfly.go
#cp tun_darwin_gvisor.go tun_dragonfly_gvisor.go
#sed -i 's|DarwinEndpoint|DragonFlyEndpoint|g;s|darwin|dragonfly|g' tun_dragonfly_gvisor.go
git diff HEAD > ../mihomo/sing-tun.patch


## build
# sing-box
os='freebsd'
arch='amd64'
sb_version='1.12.0-beta-vincent'
tags='with_gvisor,with_quic,with_dhcp,with_wireguard,with_utls,with_acme,with_clash_api,with_tailscale'
no_wg_tags='with_gvisor,with_quic,with_dhcp,with_utls,with_acme,with_clash_api'

cd ../sing-box-official
git diff HEAD > ../sing-box/sing-box.patch
if [ ${os} == "dragonfly" -o ${os} == "netbsd" ]; then
  GOOS=${os} GOARCH=${arch} CGO_ENABLED=0 go build -v -trimpath -ldflags "-X 'github.com/sagernet/sing-box/constant.Version=${sb_version}' -s -w -buildid=" -tags ${no_wg_tags} ./cmd/sing-box
else
  GOOS=${os} GOARCH=${arch} CGO_ENABLED=0 go build -v -trimpath -ldflags "-X 'github.com/sagernet/sing-box/constant.Version=${sb_version}' -s -w -buildid=" -tags ${tags} ./cmd/sing-box
fi
#rm sing-box
# mihomo
cd ../mihomo-official
git diff HEAD > ../mihomo/mihomo.patch
if [ ${os} == "dragonfly" -o ${os} == "netbsd" ]; then
  exit 1
fi
GOOS=${os} GOARCH=${arch} CGO_ENABLED=0 go build -v -tags with_gvisor -trimpath -ldflags '-X "github.com/metacubex/mihomo/constant.Version=Alpha-vincent" -X "github.com/metacubex/mihomo/constant.BuildTime=none" -w -s -buildid=' -o mihomo
#rm mihomo
