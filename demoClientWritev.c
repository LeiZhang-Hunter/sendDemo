#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>
#include <sys/uio.h>

#define WORK_NUM 2
int run = 1;
#define SEND_NUM 5

int writeBuf(int fd,char* buf,size_t len)
{
    struct iovec iov[1];
    iov[0].iov_len = len;
    iov[0].iov_base = buf;
    return writev(fd,iov,1);
}

int main()
{
    int i = 0;
    pid_t pid;
    pid_t arr[4];
    int count = 0;
    int status;
    char *data = ".csdn-toolbar .clearfix:after,.csdn-toolbar .form-horizontal .form-group:after{clear:both}.csdn-toolbar .col-sm-1,.csdn-toolbar .col-sm-10,.csdn-toolbar .col-sm-11,.csdn-toolbar .col-sm-2,.csdn-toolbar .col-sm-3,.csdn-toolbar .col-sm-4,.csdn-toolbar .col-sm-5,.csdn-toolbar .col-sm-6,.csdn-toolbar .col-sm-7,.csdn-toolbar .col-sm-8,.csdn-toolbar .col-sm-9,.csdn-toolbar .pull-left{float:left}@font-face{font-family:iconfont-toolbar;src:url(//csdnimg.cn/cdn/content-toolbar/iconfont.eot?t=1509003158575);src:url(//csdnimg.cn/cdn/content-toolbar/iconfont.eot?t=1509003158575#iefix) format('embedded-opentype'),url(//csdnimg.cn/cdn/content-toolbar/iconfont.ttf?t=1509003158575) format('truetype'),url(//csdnimg.cn/cdn/content-toolbar/iconfont.svg?t=1509003158575#iconfont) format('svg')}.h1,.h2,.h3,.h4,.h5,.h6,a,abbr,body,cite,dd,dl,dt,h1,h2,h3,h4,h5,h6,iframe,input,li,object,ol,p,pre,span,ul{font-family:'Microsoft YaHei','SF Pro Display',Roboto,Noto,Arial,'PingFang SC',sans-serif}code,kbd,pre,samp{font-family:'Source Code Pro','DejaVu Sans Mono','Ubuntu Mono','Anonymous Pro','Droid Sans Mono'}.csdn-toolbar .container .left-menu li a .iconfont-toolbar,.iconfont-toolbar{font-family:iconfont-toolbar!important;-webkit-font-smoothing:antialiased;-moz-osx-font-smoothing:grayscale;font-style:normal}.iconfont-toolbar{font-size:16px}.toolbar-xiajiantou:before{content:\"\\e843\"}.toolbar-shouji:before{content:\"\\e844\"}.toolbar-tianxie:before{content:\"\\e845\"}.toolbar-sousuo:before{content:\"\\e846\"}.toolbar-guanbi:before{content:\"\\e847\"}.toolbar-caidan:before{content:\"\\e848\"}.toolbar-yonghudenglu:before{content:\"\\e849\"}.toolbar-csdnlogo:before{content:\"\\e855\"}.toolbar-morentouxiang:before{content:\"\\e87e\"}.toolbar-icon_boke:before{content:\"\\e880\"}.toolbar-icon_gitchatx:before{content:\"\\e881\"}.toolbar-guanbi1:before{content:\"\\e882\"}.toolbar-icon{fill:currentColor;overflow:hidden}.csdn-toolbar{font-size:.75em;color:#333;line-height:1.5em;background:#fff;box-shadow:0 2px 4px 0 rgba(0,0,0,.05);min-width:1200px;width:100%;padding:0 24px;box-sizing:border-box;-moz-box-sizing:border-box;-webkit-box-sizing:border-box}#csdn_tool_otherPlace *,#csdn_tool_otherPlace :after,#csdn_tool_otherPlace :before,.csdn-toolbar *,.csdn-toolbar :after,.csdn-toolbar :before{-webkit-box-sizing:content-box;-moz-box-sizing:content-box;box-sizing:content-box}.csdn-toolbar:after{display:block;clear:both;content:\"\";visibility:hidden;height:0}.csdn-toolbar blockquote,.csdn-toolbar code,.csdn-toolbar dd,.csdn-toolbar div,.csdn-toolbar dl,.csdn-toolbar dt,.csdn-toolbar fieldset,.csdn-toolbar form,.csdn-toolbar h1,.csdn-toolbar h2,.csdn-toolbar h3,.csdn-toolbar h4,.csdn-toolbar h5,.csdn-toolbar h6,.csdn-toolbar input,.csdn-toolbar legend,.csdn-toolbar li,.csdn-toolbar p,.csdn-toolbar pre,.csdn-toolbar td,.csdn-toolbar textarea,.csdn-toolbar th,.csdn-toolbar ul{margin:0;padding:0;line-height:1.5em;text-align:left}.csdn-toolbar table{border-collapse:collapse;border-spacing:0;table-layout:fixed}.csdn-toolbar fieldset,.csdn-toolbar img{border:0}.csdn-toolbar img{display:block}#csdn_tool_otherPlace img{display:block;box-sizing:content-box;-moz-box-sizing:content-box;-webkit-box-sizing:content-box}.csdn-toolbar .clearfix:after,.csdn-toolbar .clearfix:before,.csdn-toolbar .form-horizontal .form-group:after,.csdn-toolbar .form-horizontal .form-group:before{display:table;content:\" \"}.csdn-toolbar address,.csdn-toolbar caption,.csdn-toolbar cite,.csdn-toolbar code,.csdn-toolbar dfn,.csdn-toolbar em,.csdn-toolbar strong,.csdn-toolbar th,.csdn-toolbar var{font-style:normal;font-weight:400}.csdn-toolbar ul{list-style:none}.csdn-toolbar caption,.csdn-toolbar th{text-align:left}.csdn-toolbar .clearfix{overflow:visible}.csdn-toolbar h1,.csdn-toolbar h2,.csdn-toolbar h3,.csdn-toolbar h4,.csdn-toolbar h5,.csdn-toolbar h6{font-weight:700;line-height:1.5em;color:#333;background:0 0;margin:0;text-align:left}.csdn-toolbar h1{font-size:3em}.csdn-toolbar h2{font-size:2.5em}.csdn-toolbar h3{font-size:2em}.csdn-toolbar h4{font-size:1.5em}.csdn-toolbar h5{font-size:1.166666666em}.csdn-toolbar h6{font-size:1em}.csdn-toolbar textarea{resize:none}.csdn-toolbar a:link,.csdn-toolbar a:visited{color:#333;text-decoration:none}.csdn-toolbar a:hover{text-decoration:none}.csdn-toolbar h1 a:link,.csdn-toolbar h1 a:visited,.csdn-toolbar h2 a:link,.csdn-toolbar h2 a:visited,.csdn-toolbar h3 a:link,.csdn-toolbar h3 a:visited,.csdn-toolbar h4 a:link,.csdn-toolbar h4 a:visited,.csdn-toolbar h5 a:link,.csdn-toolbar h5 a:visited,.csdn-toolbar h6 a:link,.csdn-toolbar h6 a:visited{color:#333}.csdn-toolbar h1 a:hover,.csdn-toolbar h2 a:hover,.csdn-toolbar h3 a:hover,.csdn-toolbar h4 a:hover,.csdn-toolbar h5 a:hover,.csdn-toolbar h6 a:hover{color:#c00}.csdn-toolbar a:focus{outline:0}.csdn-toolbar a.f-blue:link,.csdn-toolbar a.f-blue:visited{color:#2981a9;text-decoration:none}.csdn-toolbar a.f-blue:visited{color:#025d87;text-decoration:none}.csdn-toolbar a.f-undline:link,.csdn-toolbar a.f-undline:visited{text-decoration:underline}.csdn-toolbar .col-sm-12{width:100%}.csdn-toolbar .col-sm-11{width:91.6667%}.csdn-toolbar .col-sm-10{width:86.3333%}.csdn-toolbar .col-sm-9{width:75%}.csdn-toolbar .col-sm-8{width:66.6667%}.csdn-toolbar .col-sm-7{width:58.3333%}.csdn-toolbar .col-sm-6{width:50%}.csdn-toolbar .col-sm-5{width:41.6667%}.csdn-toolbar .col-sm-4{width:33.3333%}.csdn-toolbar .col-sm-3{width:25%}.csdn-toolbar .col-sm-2{float:left;width:16.6667%}.csdn-toolbar .col-sm-1{width:8.33333%}#csdn_tool_otherPlace .pull-right,.csdn-toolbar .pull-right{float:right;margin-right:-6px}.csdn-toolbar a{color:#999;text-decoration:none;font-size:12px;font-weight:400}.csdn-toolbar a:hover{color:#333}.csdn-toolbar dl{margin:0;font-size:12px}.csdn-toolbar li,.csdn-toolbar ul{margin:0;padding:0;height:100%}#csdn_tool_otherPlace li,.csdn-toolbar li{list-style:none;float:left;height:44px;width:auto;border:1px solid #eee;border-width:0 1px;border-right-color:#fff;position:relative;background:0 0}.csdn-toolbar .hide{display:none}.csdn-toolbar .open .dropdown-menu{display:block;min-width:70px;border-radius:0;top:23px}.csdn-toolbar .open .dropdown-menu li{width:100%;float:left;height:auto;border:0;text-align:center;color:#333;padding-right:10px}.csdn-toolbar input:focus,.csdn-toolbar textarea:focus{border-color:#9cf;outline:0;box-shadow:none}.csdn-toolbar .form-horizontal .form-group{margin:0 0 10px}.csdn-toolbar .form-horizontal .form-group .ft{margin-left:25px;padding-left:12px;width:362px}.csdn-toolbar .form-horizontal .control-label{padding:7px 10px 0 0;width:48px;text-align:right;-webkit-box-sizing:border-box;-moz-box-sizing:border-box;box-sizing:border-box}.csdn-toolbar .form-horizontal .control-label .red_txt{color:red;padding-right:3px}.csdn-toolbar .form-control{display:block;width:336px;border-radius:0;height:28px;padding:0 7px;font-size:14px;line-height:1.428571429;color:#555;vertical-align:middle;background-color:#fff;background-image:none;border:1px solid #ccc;-webkit-box-shadow:inset 0 1px 1px rgba(0,0,0,.075);box-shadow:none;-webkit-transition:border-color ease-in-out .15s,box-shadow ease-in-out .15s;transition:border-color ease-in-out .15s,box-shadow ease-in-out .15s}.csdn-toolbar textarea.form-control{height:70px;padding-top:5px}.csdn-toolbar .nobg{background:0 0!important}.csdn-toolbar .icon-enter-sm,.csdn-toolbar .icon-hasnotes-sm,.csdn-toolbar .write-icon{background-image:url(http://c.csdnimg.cn/public/common/toolbar/images/f_icon.png)}.csdn-toolbar .icon-enter-sm{background-position:0 -192px}.csdn-toolbar .icon .wrap{font-size:12px;display:none;background:#fff;border:1px solid #ccc;padding:7px;position:absolute;top:30px;box-shadow:0 3px 2px rgba(0,0,0,.15)}.csdn-toolbar .icon .curr-icon-wrap{border-bottom:1px solid #fff;height:3px;position:absolute;top:-4px;width:41px}body .csdn-toolbar .container{width:1200px;margin:0 auto}body .csdn-toolbar .container .left-menu{margin-left:-6px}.csdn-toolbar .container .left-menu .csdn-logo{width:90px;display:block}.csdn-toolbar .container:after,.csdn-toolbar .container:before{content:\" \";display:table}#csdn_tool_otherPlace li,.csdn-toolbar .container li{border-left:none;border-right:none;width:auto;padding-left:8px;padding-right:8px;-webkit-transition:background-color .5s;transition:background-color .5s}#csdn_tool_otherPlace .pull-right li a,.csdn-toolbar .container .pull-right li a{display:inline-block;text-align:center;color:#3D3D3D}.csdn-toolbar .container .left-menu li a{display:inline-block;height:43px;line-height:44px;text-align:center;font-size:14px;color:#666C7A}.csdn-toolbar .container .left-menu li:first-child a{width:90px;height:44px}.csdn-toolbar .container .left-menu li:first-child{padding-left:0}.csdn-toolbar .container .left-menu li:first-child a:hover,.csdn-toolbar .container .left-menu li:first-child:hover{background:0 0}.csdn-toolbar .container .left-menu li .active{border-bottom:2px solid #D92E2E;color:#222429}body .csdn-toolbar .container .left-menu li:first-child a svg{width:80px;height:40px}#csdn_tool_otherPlace .pull-right,.csdn-toolbar .container .pull-right{height:44px}#csdn_tool_otherPlace .pull-right ul,#csdn_tool_otherPlace .pull-right ul li,.csdn-toolbar .container .pull-right ul,.csdn-toolbar .container .pull-right ul li{height:100%}#csdn_tool_otherPlace .pull-right li a,.csdn-toolbar .container .pull-right li a{height:44px;line-height:44px}.csdn-toolbar .container .left-menu .show-more{width:70px}.csdn-toolbar .container .left-menu .show-more .more div a{padding-left:10px;padding-right:10px;height:32px;line-height:32px}.csdn-toolbar .container .left-menu .show-more .more div:last-child a{padding-bottom:4px}.csdn-toolbar .container .left-menu li a .iconfont-toolbar{font-size:16px;margin:0 3px;color:#788087;vertical-align:middle;display:inline-block;-webkit-transition:-webkit-transform .5s,transform .5s;transition:-webkit-transform .5s,transform .5s;-webkit-transform-origin:50% 48%;-moz-transform-origin:50% 48%;-ms-transform-origin:50% 48%;-o-transform-origin:50% 48%;transform-origin:50% 48%}#csdn_tool_otherPlace .pull-right .userinfo a:hover,.csdn-toolbar .container .left-menu li a:hover,.csdn-toolbar .container .pull-right .userinfo a:hover{color:#222429}.csdn-toolbar .container .left-menu .show-more .more{display:none;position:relative;z-index:99999;background-color:#fff;border-radius:0 0 4px 4px;box-shadow:0 4px 8px 0 rgba(0,0,0,.1);width:125px;left:-24px;top:7px;padding-bottom:12px;padding-top:8px;float:inherit}#csdn_tool_otherPlace .pull-right .userinfo:hover,.csdn-toolbar .container .left-menu li:hover,.csdn-toolbar .container .left-menu li:hover i,.csdn-toolbar .container .pull-right .userinfo:hover{background:#F0F1F2}.csdn-toolbar .container .left-menu .show-more:hover a i{-webkit-transform:rotate(-180deg);-moz-transform:rotate(-180deg);-ms-transform:rotate(-180deg);-o-transform:rotate(-180deg);transform:rotate(-180deg)}.csdn-toolbar .container .show-more a .icon-xiajiantou{position:relative;top:-1px}#csdn_tool_otherPlace .left-menu .more div:last-child,#csdn_tool_otherPlace .pull-right .userControl div:last-child,.csdn-toolbar .container .left-menu .more div:last-child,.csdn-toolbar .container .pull-right .userControl div:last-child{border-bottom:none}#csdn_tool_otherPlace .pull-right .userinfo,.csdn-toolbar .container .pull-right .userinfo{display:none}#csdn_tool_otherPlace .pull-right .userinfo a,.csdn-toolbar .container .pull-right .userinfo a{display:inline-block;padding-right:0;color:#222429;font-size:14px}#csdn_tool_otherPlace .pull-right .userinfo span,.csdn-toolbar .container .pull-right .userinfo span{color:#888}#csdn_tool_otherPlace .pull-right .userLogin,.csdn-toolbar .container .pull-right .userLogin{display:block;position:relative}#csdn_tool_otherPlace .pull-right .userLogin .guo_tip_box,#csdn_tool_otherPlace .pull-right .write-bolg-btn .blog_tip_box,.csdn-toolbar .container .pull-right .userLogin .guo_tip_box,.csdn-toolbar .container .pull-right .write-bolg-btn .blog_tip_box{position:absolute;top:30px;left:-26px;width:112px;height:32px;line-height:32px;-moz-border-radius:12px;-webkit-border-radius:12px;border-radius:4px;background:rgba(15,15,15,.8);color:#fff;font-size:12px;text-align:center;cursor:pointer;display:none;z-index:3000}#csdn_tool_otherPlace .pull-right .write-bolg-btn .blog_tip_box,.csdn-toolbar .container .pull-right .write-bolg-btn .blog_tip_box{width:160px}#csdn_tool_otherPlace .pull-right .userLogin .guo_tip_box:before,#csdn_tool_otherPlace .pull-right .write-bolg-btn .blog_tip_box:before,.csdn-toolbar .container .pull-right .userLogin .guo_tip_box:before,.csdn-toolbar .container .pull-right .write-bolg-btn .blog_tip_box:before{position:absolute;content:\"\";width:0;height:0;right:54px;top:-8px;border-top:4px solid transparent;border-left:4px solid transparent;border-right:4px solid transparent;border-bottom:4px solid rgba(15,15,15,.8)}#csdn_tool_otherPlace .pull-right .write-bolg-btn .blog_tip_box:before,.csdn-toolbar .container .pull-right .write-bolg-btn .blog_tip_box:before{right:72px}#csdn_tool_otherPlace .pull-right .userLogin .login_img,.csdn-toolbar .container .pull-right .userLogin .login_img{color:#D4D4D4;width:28px;height:28px;border-radius:50%;display:inline-block;margin-top:7px;background-color:#eee;vertical-align:top}#csdn_tool_otherPlace .pull-right .userLogin .loginCenter,.csdn-toolbar .container .pull-right .userLogin .loginCenter{line-height:27px;position:relative;width:25px;height:30px}#csdn_tool_otherPlace .pull-right .userLogin .userControl:hover+.loginCenter,.csdn-toolbar .container .pull-right .userLogin .userControl:hover+.loginCenter{background:#F4F5F6;border-radius:3px}#csdn_tool_otherPlace .pull-right .userLogin .loginCenter .userName,.csdn-toolbar .container .pull-right .userLogin .loginCenter .userName{display:inline-block;overflow-x:hidden;text-overflow:ellipsis;white-space:nowrap;max-width:106px}#csdn_tool_otherPlace .pull-right .userLogin .loginCenter a,.csdn-toolbar .container .pull-right .userLogin .loginCenter a{padding-left:0;padding-right:0;width:25px;height:24px;display:inline-block}#csdn_tool_otherPlace .pull-right .userLogin .loginCenter a:hover,#csdn_tool_otherPlace .pull-right .userLogin .loginCenter a:hover i,.csdn-toolbar .container .pull-right .userLogin .loginCenter a:hover,body .csdn-toolbar .container .pull-right .userLogin .loginCenter a:hover i{color:#c92027}#csdn_tool_otherPlace .pull-right .userLogin .loginCenter span,.csdn-toolbar .container .pull-right .userLogin .loginCenter span{padding-left:8px;padding-right:2px}#csdn_tool_otherPlace .pull-right .userControl,.csdn-toolbar .container .pull-right .userControl{display:none;position:absolute;padding-top:8px;top:44px;right:0;z-index:99999;background-color:#fff;border-radius:0 0 4px 4px;box-shadow:0 4px 8px 0 rgba(0,0,0,.1);width:124px;box-sizing:border-box;padding-bottom:8px}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon,.csdn-toolbar .container .pull-right .userControl div .pull_icon{display:inline-block;width:16px;height:16px;margin-right:8px;vertical-align:middle;margin-top:-3px}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon1,.csdn-toolbar .container .pull-right .userControl div .pull_icon1{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-gz@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon2,.csdn-toolbar .container .pull-right .userControl div .pull_icon2{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-sc@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon3,.csdn-toolbar .container .pull-right .userControl div .pull_icon3{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-yx@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon4,.csdn-toolbar .container .pull-right .userControl div .pull_icon4{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-yh@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon5,.csdn-toolbar .container .pull-right .userControl div .pull_icon5{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-yc@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon6,.csdn-toolbar .container .pull-right .userControl div .pull_icon6{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-gl@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon7,.csdn-toolbar .container .pull-right .userControl div .pull_icon7{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-sz@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon8,.csdn-toolbar .container .pull-right .userControl div .pull_icon8{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-cb@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon9,.csdn-toolbar .container .pull-right .userControl div .pull_icon9{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-dd@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon10,.csdn-toolbar .container .pull-right .userControl div .pull_icon10{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-bz@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon11,.csdn-toolbar .container .pull-right .userControl div .pull_icon11{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-tc@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon12,.csdn-toolbar .container .pull-right .userControl div .pull_icon12{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-edu@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl div .pull_icon13,.csdn-toolbar .container .pull-right .userControl div .pull_icon13{background-image:url(https://csdnimg.cn/public/common/toolbar/images/toolbar-download@2x.png);background-size:100% 100%}#csdn_tool_otherPlace .pull-right .userControl .bord,.csdn-toolbar .container .pull-right .userControl .bord{border-bottom:1px solid #E0E0E0;box-sizing:border-box}#csdn_tool_otherPlace .pull-right .userControl .bord:last-child,.csdn-toolbar .container .pull-right .userControl .bord:last-child{border:none}#csdn_tool_otherPlace .pull-right .userControl .bord div,.csdn-toolbar .container .pull-right .userControl .bord div{padding:0 16px}#csdn_tool_otherPlace .pull-right .userControl div a,.csdn-toolbar .container .pull-right .userControl div a{text-align:left;font-size:14px;color:#3D3D3D;height:40px;line-height:40px}#csdn_tool_otherPlace .pull-right .userControl div a .toolbar-newsL,.csdn-toolbar .container .pull-right .userControl div a .toolbar-newsL{display:none;color:#c92027}#csdn_tool_otherPlace .pull-right .userControl .bord div:hover,.csdn-toolbar .container .pull-right .userControl .bord div:hover{background:#F0F1F2}#csdn_tool_otherPlace .pull-right .userControl .bord div a:hover,.csdn-toolbar .container .pull-right .userControl .bord div a:hover{color:#222429}#csdn_tool_otherPlace .pull-right .userControl div:last-child a,.csdn-toolbar .container .pull-right .userControl div:last-child a{padding-bottom:4px}#csdn_tool_otherPlace .pull-right .btns .userLogin .loginCenter a i,.csdn-toolbar .container .pull-right .btns .userLogin .loginCenter a i{color:#788087;display:inline-block;vertical-align:top;transition:-webkit-transform .3s,transform .3s;-webkit-transform-origin:50% 48%;-moz-transform-origin:50% 48%;-ms-transform-origin:50% 48%;-o-transform-origin:50% 48%;transform-origin:50% 48%}#csdn_tool_otherPlace .pull-right .btns .userLogin:hover .loginCenter a i,.csdn-toolbar .container .pull-right .btns .userLogin:hover .loginCenter a i{-webkit-transform:rotate(-180deg);-moz-transform:rotate(-180deg);-ms-transform:rotate(-180deg);-o-transform:rotate(-180deg);transform:rotate(-180deg)}#csdn_tool_otherPlace .pull-right li a .icon-shouji,.csdn-toolbar .container .pull-right li a .icon-shouji{color:#D4D4D4;margin-right:3px;position:relative;display:inline-block;top:-2px;left:2px;width:19px;vertical-align:middle}#csdn_tool_otherPlace .pull-right li a .icon-tianxie,.csdn-toolbar .container .pull-right li a .icon-tianxie{color:#D4D4D4;margin-right:6px;vertical-align:middle;position:relative;top:-2px;left:2px;width:19px}.loginCenter .icon-xiajiantou{vertical-align:top}#csdn_tool_otherPlace .pull-right .gitChat a,.csdn-toolbar .container .pull-right .gitChat a{padding-left:0;padding-right:0;height:44px;line-height:44px;color:#fff;text-align:right;vertical-align:top}#csdn_tool_otherPlace .pull-right .gitChat a:hover span,.csdn-toolbar .container .pull-right .gitChat a:hover span{color:#CA0C16}#csdn_tool_otherPlace .pull-right .gitChat a svg,.csdn-toolbar .container .pull-right .gitChat a svg{margin-right:2px;fill:#F59701}#csdn_tool_otherPlace .pull-right .upload a svg,.csdn-toolbar .container .pull-right .upload a svg{fill:#3399EA}#csdn_tool_otherPlace .pull-right .gitChat a span,#csdn_tool_otherPlace .pull-right .write-bolg-btn a span,.csdn-toolbar .container .pull-right .gitChat a span,.csdn-toolbar .container .pull-right .write-bolg-btn a span{font-size:14px;color:#D92E2E;vertical-align:super}#csdn_tool_otherPlace .pull-right .gitChat a .money,.csdn-toolbar .container .pull-right .gitChat a .money{width:20px;max-height:20px;display:inline-block!important;margin-right:4px;margin-top:-12px}#csdn_tool_otherPlace .pull-right .gitChat a .message,.csdn-toolbar .container .pull-right .gitChat a .message{width:16px;display:inline-block!important;margin-top:14px;vertical-align:top}#csdn_tool_otherPlace .pull-right #msgList-other,.csdn-toolbar .container .pull-right #msgList-other{display:none}#csdn_tool_otherPlace .pull-right .write-bolg-btn a,.csdn-toolbar .container .pull-right .write-bolg-btn a{border-radius:50%;height:44px;color:#fff;padding-left:0;padding-right:0;line-height:44px}#csdn_tool_otherPlace .pull-right .write-bolg-btn:hover,.csdn-toolbar .container .pull-right .write-bolg-btn:hover{background:#FFF2F0}#csdn_tool_otherPlace .pull-right .write-bolg-btn a:hover span,.csdn-toolbar .container .pull-right .write-bolg-btn a:hover span{color:#CA0C16}#csdn_tool_otherPlace .pull-right .gitChat a .message-icon,.csdn-toolbar .container .pull-right .gitChat a .message-icon{background-image:url(https://csdnimg.cn/public/common/toolbar/images/message-icon.svg);background-repeat:no-repeat;padding-left:22px;background-position:0 1px;padding-bottom:1px}#csdn_tool_otherPlace .pull-right .write-bolg-btn a svg,.csdn-toolbar .container .pull-right .write-bolg-btn a svg{fill:#CA0C16;margin-right:3px}#csdn_tool_otherPlace .pull-right .gitChat a svg,#csdn_tool_otherPlace .pull-right .write-bolg-btn a img,.csdn-toolbar .container .pull-right .gitChat a svg,.csdn-toolbar .container .pull-right .write-bolg-btn a img{width:17px;height:17px}#csdn_tool_otherPlace .pull-right .write-bolg-btn a img,.csdn-toolbar .container .pull-right .write-bolg-btn a img{float:left;padding-top:14px;padding-right:1px}#csdn_tool_otherPlace .unlogin .userinfo,.csdn-toolbar .container .unlogin .userinfo{display:block}#csdn_tool_otherPlace .unlogin .btns .userLogin,.csdn-toolbar .container .unlogin .btns .userLogin{display:none}#csdn_tool_otherPlace .search_bar,.csdn-toolbar .container .search_bar{float:right;width:222px;height:32px;border-radius:5px;background:#F5F6F7;margin:6px 0 0 8px;transition:width .5s;-moz-transition:width .5s;-webkit-transition:width .5s;-o-transition:width .5s;transition-delay:.1s;-moz-transition-delay:.1s;-webkit-transition-delay:.1s;-o-transition-delay:.1s}#csdn_tool_otherPlace .search_bar-active,.csdn-toolbar .container .search_bar-active{width:240px;transition:width .5s;-moz-transition:width .5s;-webkit-transition:width .5s;-o-transition:width .5s;transition-delay:.1s;-moz-transition-delay:.1s;-webkit-transition-delay:.1s;-o-transition-delay:.1s}#csdn_tool_otherPlace .search_bar-active .input_search,.csdn-toolbar .container .search_bar-active .input_search{width:196px;transition:width .5s;-moz-transition:width .5s;-webkit-transition:width .5s;-o-transition:width .5s;transition-delay:.1s;-moz-transition-delay:.1s;-webkit-transition-delay:.1s;-o-transition-delay:.1s}#csdn_tool_otherPlace .search_bar .input_search,.csdn-toolbar .container .search_bar .input_search{font-size:14px;color:#666C7A;display:block;float:left;width:178px;padding-left:12px;border:0;height:32px;border-radius:5px;background:0 0}#csdn_tool_otherPlace .search_bar .input_search::-webkit-input-placeholder,.csdn-toolbar .container .search_bar .input_search::-webkit-input-placeholder{color:#c2c2c2;font-weight:300}#csdn_tool_otherPlace .search_bar .btn-search,#csdn_tool_otherPlace .search_bar .btn_clear,.csdn-toolbar .container .search_bar .btn-search,.csdn-toolbar .container .search_bar .btn_clear{background-color:rgba(0,0,0,0);color:#ccc;font-size:14px;display:block;text-align:center;width:32px;height:32px;float:right;line-height:32px;margin-top:0;-webkit-transition:background-color .5s;transition:background-color .5s}#csdn_tool_otherPlace .search_bar .btn-search-active,#csdn_tool_otherPlace .search_bar .btn-search:hover,.csdn-toolbar .container .search_bar .btn-search-active,.csdn-toolbar .container .search_bar .btn-search:hover{background:rgba(165,171,184,.2);border-top-right-radius:5px;border-bottom-right-radius:5px;-webkit-transition:background-color .5s;transition:background-color .5s}#csdn_tool_otherPlace .search_bar .btn_clear:hover,.csdn-toolbar .container .search_bar .btn_clear:hover{color:#999}.bdSug_wpr,.bdSug_wpr td,.bdsug_copy{color:#666C7A!important}#csdn_tool_otherPlace .search_bar a,.csdn-toolbar .container .search_bar a{margin-top:3px}#csdn_tool_otherPlace .search_bar a img,.csdn-toolbar .container .search_bar a img{width:32px;height:32px}.csdn-toolbar .icon{background-image:none}.csdn-toolbar .btn:active,.csdn-toolbar .btn:focus{outline:0;border:0;box-shadow:0 0 0 transparent}.csdn-toolbar .container .show-more .show-more-a{padding:0;width:46px;height:35px;border-radius:3px;margin:7px 0 0 13px}.csdn-toolbar .container .show-more .show-more-a svg{position:absolute;top:22px;left:26px}.csdn-toolbar .container .show-more .show-more-a:hover{background:#F4F5F6}.bdSug_wpr td{padding-left:16px!important;padding-right:16px!important}.bdSug_wpr tr{line-height:35px!important;height:35px!important}.bdSug_app{padding:8px!important}.bdSug_wpr{border-radius:4px!important;color:rgba(102,108,122,1)!important;border:none!important;padding-top:8px!important;box-shadow:0 4px 8px 0 rgba(0,0,0,.1)}.bdSug_wpr tr:hover{background:#F0F1F2!important;color:#666C7A!important}.csdn-toolbar .tb_is1260hide,.csdn-toolbar .tb_is1320hide,.csdn-toolbar .tb_is1380hide,.csdn-toolbar .tb_is1440hide{display:none}.csdn-toolbar .tb_is1260show,.csdn-toolbar .tb_is1320show,.csdn-toolbar .tb_is1380show,.csdn-toolbar .tb_is1440show{display:block}.csdn-toolbar .tb_show{display:none}@media(min-width:1260px){.csdn-toolbar .tb_is1260hide{display:block}.csdn-toolbar .tb_is1260show{display:none}}@media(min-width:1320px){.csdn-toolbar .tb_is1320hide{display:block}.csdn-toolbar .tb_is1320show,.tb_bbs .tb_is1320hide{display:none}.tb_bbs .tb_is1320show{display:block}}@media(min-width:1380px){.csdn-toolbar .tb_is1380hide{display:block}.csdn-toolbar .tb_is1380show,.tb_bbs .tb_is1380hide{display:none}.tb_bbs .tb_is1380show{display:block}}@media(min-width:1440px){.csdn-toolbar .show-more{display:none}.csdn-toolbar .tb_is1440hide{display:block}.csdn-toolbar .tb_is1440show{display:none}.tb_bbs .show-more{display:block}.tb_bbs .tb_is1440hide{display:none}.tb_bbs .tb_is1440show{display:block}}@media(min-width:1540px){.tb_bbs .tb_is1320hide{display:block}.tb_bbs .tb_is1320show{display:none}}@media(min-width:1568px){.tb_bbs .tb_is1380hide{display:block}.tb_bbs .tb_is1380show{display:none}}@media(min-width:1680px){.tb_bbs .show-more{display:none}.tb_bbs .tb_is1440hide{display:block}.tb_bbs .tb_is1440show{display:none}}.csdn-bbs .topic-list .csdn-toolbar{padding:0 24px}.csdn-toolbar .toolbar-prompt-box{background:rgba(51,51,51,.8);position:absolute;bottom:-32px;z-index:1;display:none;font-size:14px;padding:0 8px}.toolbar-prompt-box span{white-space:nowrap;font-size:13px}.toolbar-prompt-box .arrow{position:absolute;top:-5px;left:50%;width:0;height:0;border-style:solid;border-width:0 5px 5px;border-color:transparent transparent rgba(51,51,51,.9)}.toolbar_speck{position:absolute;top:12px;right:14px;width:6px;height:6px;border-radius:50%;background-color:#e74040}.toolbar-circle{display:none;background-color:#CA0C16;border-radius:16px;padding:0 3px!important;position:absolute;top:3px;right:-1px;color:#fff;font-size:xx-small;transform:scale(.8);vertical-align:middle;line-height:16px!important;height:16px;min-width:11px;border:1px solid #FFF;text-align:center!important}.csdn-toolbar .container .app-control,.csdn-toolbar .container .baidu-app-btn,.csdn-toolbar .container li.vip-caise{position:relative}html body .csdn-toolbar .tb_disnone{display:none}html body .csdn-toolbar .icon{margin:0}.vip-caise img{display:inline-block!important;padding-right:2px;vertical-align:sub;width:20px}.vip-caise .vip-totast{display:inline-block;width:44px;color:#FF700A;transform:scale(.9);white-space:nowrap}@media screen and (max-width:1298px){.vip-caise .vip-totast{display:none}}.vip-caise .vip-totast img{max-width:100%;padding-right:0;width:auto;height:auto;vertical-align:unset}.csdn-toolbar .container .app-control .appControl{width:122px}.csdn-toolbar .container .app-control .appControl,.csdn-toolbar .container .baidu-app-btn .baiduControl{display:none;position:absolute;padding:16px 16px 39px;top:39px;left:-96px;z-index:99999;background-color:#fff;border-radius:4px;box-shadow:0 4px 8px 0 rgba(0,0,0,.1);box-sizing:border-box}.csdn-toolbar .container .baidu-app-btn .baiduControl{top:31px;left:-39px;width:160px;text-align:center;z-index:999}.csdn-toolbar .container .baidu-app-btn a{cursor:default}.csdn-toolbar .container .baidu-app-btn .baiduControl p{text-align:center;font-size:14px;line-height:16px;margin-bottom:6px}.csdn-toolbar .container .app-control .appControl{left:-40px}.csdn-toolbar .container .app-control .appControl span,.csdn-toolbar .container .baidu-app-btn .baiduControl span{display:inline-block;position:relative;text-align:center;font-size:0;vertical-align:middle}.csdn-toolbar .container .app-control .appControl em,.csdn-toolbar .container .baidu-app-btn .baiduControl em{display:inline-block;position:absolute;left:0;bottom:-26px;width:100%;font-style:normal;font-size:14px;vertical-align:middle}.csdn-toolbar .container .app-control img,.csdn-toolbar .container .baidu-app-btn img{width:90px}.app-control .appControl .eduwx em{bottom:-27px}.msgBox{position:relative}.msgBox .msgTitle{height:26px;line-height:26px;padding:0;margin-left:14px;text-align:right}.msgList{min-width:120px;display:none;padding:8px 0!important;position:absolute;top:44px;z-index:3001;background-color:#FFF;box-shadow:0 2px 4px 0 rgba(0,0,0,.1);border-radius:3px;font-size:14px;left:50%;transform:translateX(-50%)}.msgList dd{padding-left:16px;padding-right:16px;white-space:nowrap}.msgList dd:hover{background:#F0F1F2}#csdn_tool_otherPlace .pull-right .msgList dd a:hover,.csdn-toolbar .container .pull-right .msgList dd a:hover{color:#222429}#csdn_tool_otherPlace .pull-right .msgList dd a,.csdn-toolbar .container .pull-right .msgList dd a{display:block;height:40px;font-size:14px;color:#3D3D3D;letter-spacing:0;line-height:40px;text-align:left;border-radius:unset}.msgList a em{display:inline-block;margin-left:8px;font-style:normal;color:#cc1b25;line-height:0!important}#csdn_tool_otherPlace .pull-right .gitChat .msg-toast,#csdn_tool_otherPlace .pull-right .userinfo .msg-toast,.csdn-toolbar .container .pull-right .gitChat .msg-toast,.csdn-toolbar .container .pull-right .userinfo .msg-toast{display:none;height:auto;padding:8px;position:absolute;left:50%;transform:translateX(-50%);top:36px;background:rgba(15,15,15,.8);border-radius:4px;font-size:12px;color:#fff;line-height:1.5;text-align:center;max-width:200px;min-width:160px;z-index:3000}#csdn_tool_otherPlace .pull-right .userinfo .msg-toast,.csdn-toolbar .container .pull-right .userinfo .msg-toast{left:31%;text-decoration:underline}#csdn_tool_otherPlace .pull-right .userinfo .msg-toast:hover,.csdn-toolbar .container .pull-right .userinfo .msg-toast:hover{color:#fff}.msg-toast:after{position:absolute;left:50%;top:-12px;margin-left:-3px;content:'';border-style:solid;border-color:rgba(15,15,15,.8);border-width:6px;border-left-color:transparent;border-top-color:transparent;border-right-color:transparent}#csdn_tool_otherPlace .pull-right .userinfo .msg-toast:after,.csdn-toolbar .container .pull-right .userinfo .msg-toast:after{display:none}.msg-toast--show{display:inline-block!important}.indexSuperise .showBig div.pos-box a{display:block}.pre-img-lasy{visibility:hidden;position:absolute}.container-fluid{top:44px}#csdn_tool_otherPlace{float:left}#csdn_tool_otherPlace .search_bar{float:left;width:222px;height:32px;border-radius:5px;background:#F5F6F7;margin:6px 40px 0 8px;transition:width .5s;-moz-transition:width .5s;-webkit-transition:width .5s;-o-transition:width .5s;transition-delay:.1s;-moz-transition-delay:.1s;-webkit-transition-delay:.1s;-o-transition-delay:.1s}#csdn_tool_otherPlace .write-bolg-btn{display:none}\n\0";

    int socket_fd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    int res = connect(socket_fd,(struct sockaddr*)&addr,sizeof(addr));
    if(res < 0)
    {
        printf("%d;%s\n",errno,strerror(errno));
        exit(-1);
    }

    for(i = 0;i<WORK_NUM;i++) {
        pid = fork();
        sigset_t set;
        sigset_t old_set;
        sigfillset(&set);
        sigprocmask(SIG_BLOCK,&set,&old_set);
        //子进程
        if(pid == 0)
        {
            while (1)
            {
                if(count == SEND_NUM)
                {
                    break;
                }
                printf("size:%ld\n",strlen(data)+1);
                ssize_t res = writeBuf(socket_fd,data,strlen(data)+1);
                if(res < 0)
                {
                    printf("%d;%s\n",errno,strerror(errno));
                }


                count++;
            }
            _exit(0);
        }else if(pid > 0)
        {
            arr[i] = pid;
        }
    }

    //wait等待子进程执行完毕
    for(i=0;i<WORK_NUM;i++)
    {
        waitpid(arr[i],&status,0);
    }
    printf("%s\n","end");
    return 0;
}

