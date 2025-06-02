cd ../sing-tun
cp monitor_darwin.go monitor_freebsd.go
cp tun_darwin_gvisor.go tun_freebsd_gvisor.go
sed -i 's|DarwinEndpoint|FreeBSDEndpoint|g;s|darwin|freebsd|g' tun_freebsd_gvisor.go
cp monitor_darwin.go monitor_openbsd.go
cp tun_darwin_gvisor.go tun_openbsd_gvisor.go
sed -i 's|DarwinEndpoint|OpenBSDEndpoint|g;s|darwin|openbsd|g' tun_openbsd_gvisor.go
git diff HEAD > ../sing-box/sing-tun.patch

cd ../sing-tun-meta
cp monitor_darwin.go monitor_freebsd.go
cp tun_darwin_gvisor.go tun_freebsd_gvisor.go
sed -i 's|DarwinEndpoint|FreeBSDEndpoint|g;s|darwin|freebsd|g' tun_freebsd_gvisor.go
git diff HEAD > ../mihomo/sing-tun.patch

os='freebsd'
arch='amd64'
sb_version='1.12.0-beta-vincent'
cd ../sing-box-official
git diff HEAD > ../sing-box/sing-box.patch
GOOS=${os} GOARCH=${arch} CGO_ENABLED=0 go build -v -trimpath -ldflags "-X 'github.com/sagernet/sing-box/constant.Version=${sb_version}' -s -w -buildid=" -tags with_gvisor,with_dhcp,with_wireguard,with_utls,with_acme,with_clash_api,with_tailscale,with_quic ./cmd/sing-box
#rm sing-box

cd ../mihomo-official
git diff HEAD > ../mihomo/mihomo.patch
GOOS=${os} GOARCH=${arch} CGO_ENABLED=0 go build -v -tags with_gvisor -trimpath -ldflags '-X "github.com/metacubex/mihomo/constant.Version=Alpha-vincent" -X "github.com/metacubex/mihomo/constant.BuildTime=none" -w -s -buildid=' -o mihomo
#rm mihomo
