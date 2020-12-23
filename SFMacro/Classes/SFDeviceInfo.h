//
//  SFDeviceInfo.h
//  SFMacro_Example
//
//  Created by 黄山锋 on 2020/12/20.
//  Copyright © 2020 jack110530. All rights reserved.
//

#ifndef SFDeviceInfo_h
#define SFDeviceInfo_h

// MARK: iOS版本
// 系统版本
#define SFSystemVersion                             [[UIDevice currentDevice] systemVersion]
// =
#define SFSystemVersionIsEqualTo(v)                 ([SFSystemVersion compare:v options:NSNumericSearch] == NSOrderedSame)
// >
#define SFSystemVersionIsGreaterThan(v)             ([SFSystemVersion compare:v options:NSNumericSearch] == NSOrderedDescending)
// >=
#define SFSystemVersionIsGreaterThanOrEqualTo(v)    ([SFSystemVersion compare:v options:NSNumericSearch] != NSOrderedAscending)
// <
#define SFSystemVersionIsLessThan(v)                ([SFSystemVersion compare:v options:NSNumericSearch] == NSOrderedAscending)
// <=
#define SFSystemVersionIsLessThanOrEqualTo(v)       ([SFSystemVersion compare:v options:NSNumericSearch] != NSOrderedDescending)


// MARK: 机型
// 判断是否为iPhone
#define SFIsIPhone          (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPhone)
// 判断是否为iPad
#define SFIsIPad            (UI_USER_INTERFACE_IDIOM() == UIUserInterfaceIdiomPad)
// iPhone4S
#define SFIsIPhone4S        ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 960), [[UIScreen mainScreen] currentMode].size) : NO)
// iPhone5 iPhone5s iPhoneSE
#define SFIsIPhone5         ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size) : NO)
// iPhone6 7 8
#define SFIsIPhone6         ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? (CGSizeEqualToSize(CGSizeMake(750, 1334), [[UIScreen mainScreen] currentMode].size) || CGSizeEqualToSize(CGSizeMake(640, 1136), [[UIScreen mainScreen] currentMode].size)) : NO)
// iPhone6plus  iPhone7plus iPhone8plus
#define SFIsIPhone6Plus     ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? (CGSizeEqualToSize(CGSizeMake(1125, 2001), [[UIScreen mainScreen] currentMode].size) || CGSizeEqualToSize(CGSizeMake(1242, 2208), [[UIScreen mainScreen] currentMode].size)) : NO)
// iPhoneX
#define SFIsIPhoneX         ([UIScreen instancesRespondToSelector:@selector(currentMode)] ? CGSizeEqualToSize(CGSizeMake(1125, 2436), [[UIScreen mainScreen] currentMode].size) : NO)


// MARK: 屏幕尺寸
#define SFScreenScale       getScreenScale()
#define SFScreenSize        getScreenSize()
#define SFScreenWidth       SFScreenSize.width
#define SFScreenHeight      SFScreenSize.height


// MARK: 页面高度
#define SFStatusBarHeight       getStatusBarHeight()                 //状态栏高度
#define SFNavBarHeight          44.0                                 //导航栏高度
#define SFTopHeight             (SFStatusBarHeight + SFNavBarHeight) // 导航栏+状态栏的高度
#define SFSafeBottomHeight      (SFStatusBarHeight>20?34:0)          // 底部安全高度
#define SFTabBarHeight          49.0                                 // tabBar的高度
#define SFBottomHeight          (SFSafeBottomHeight+SFTabBarHeight)  // tabBar+底部安全的高度


// MARK: 根据iPhone6为基准的缩放比例
#define SFWidthScaleByIphone6(width)       (width*(SFScreenWidth/375.0f))
#define SFHeightScaleByIphone6(height)     (height*(SFScreenHeight/667.0f))


// MARK: 字体大小
#define SFFontSizeScale                     (SFIsIPhone6Plus ? 1.2 : 1.0)
#define SFFontSize(value)                   (value*SFFontSizeScale)
#define SFFont(value)                       [UIFont systemFontOfSize:SFFontSize(value)]
#define SFFontBold(value)                   [UIFont boldSystemFontOfSize:SFFontSize(value)]



#pragma mark - private func
CGFloat getScreenScale() {
    static CGFloat scale;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        scale = [UIScreen mainScreen].scale;
    });
    return scale;
}

CGSize getScreenSize() {
    static CGSize size;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        size = [UIScreen mainScreen].bounds.size;
        if (size.height < size.width) {
            CGFloat tmp = size.height;
            size.height = size.width;
            size.width = tmp;
        }
    });
    return size;
}

CGFloat getStatusBarHeight() {
    static CGFloat statusBarHeight;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        if (@available(iOS 13.0, *)) {
            UIStatusBarManager *statusBarManager = [UIApplication sharedApplication].windows.firstObject.windowScene.statusBarManager;
            statusBarHeight = statusBarManager.statusBarFrame.size.height;
        }
        else {
            statusBarHeight = [UIApplication sharedApplication].statusBarFrame.size.height;
        }
    });
    return statusBarHeight;
}



#endif /* SFDeviceInfo_h */
