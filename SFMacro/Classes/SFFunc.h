//
//  SFFunc.h
//  SFMacro_Example
//
//  Created by 黄山锋 on 2020/12/20.
//  Copyright © 2020 jack110530. All rights reserved.
//

#ifndef SFFunc_h
#define SFFunc_h


// MARK: NSLog
#ifdef DEBUG
#define NSLog(...) NSLog(@"%s 第%d行 \n %@\n\n",__func__,__LINE__,[NSString stringWithFormat:__VA_ARGS__])
#else
#define NSLog(...)
#endif


// MARK: 懒加载
#define SFLazyLoadCode(class, property, handle) \
- (class *)property {\
if (!_##property) {\
handle;\
}\
return _##property;\
}\

// MARK: 字符串拼接
#define SFStringFormatCode(fmt, ...) [NSString stringWithFormat:fmt, __VA_ARGS__]

// MARK: 本地化
#define SFString(key) NSLocalizedStringFromTable(key, @"Localizable", nil)

// MARK: 判空处理
//字符串是否为空
#define SFStringIsEmpty(str) ([str isEqualToString:@"null"] || [str isEqualToString:@"Null"] || [str isKindOfClass:[NSNull class]] || str == nil || [str length] < 1 ? YES : NO )
//数组是否为空
#define SFArrayIsEmpty(array) (array == nil || [array isKindOfClass:[NSNull class]] || array.count == 0)
//字典是否为空
#define SFDictIsEmpty(dic) (dic == nil || [dic isKindOfClass:[NSNull class]] || dic.allKeys == 0)
//是否是空对象
#define SFObjectIsEmpty(_object) (_object == nil || [_object isKindOfClass:[NSNull class]] || ([_object respondsToSelector:@selector(length)] && [(NSData *)_object length] == 0) || ([_object respondsToSelector:@selector(count)] && [(NSArray *)_object count] == 0))

// MARK: 单例写法
#define SFSingleton_h(name)  +(instancetype)shared##name;

#if __has_feature(objc_arc) // arc环境
#define SFSingleton_m(name)  +(instancetype)shared##name{ \
static id instance = nil; \
static dispatch_once_t onceToken;\
dispatch_once(&onceToken, ^{\
instance = [[self alloc] init];\
});\
return instance;\
}\
\
+ (instancetype)allocWithZone:(struct _NSZone *)zone {\
static id instance = nil;\
static dispatch_once_t onceToken;\
dispatch_once(&onceToken, ^{\
instance = [super allocWithZone:zone];\
});\
return instance;\
}\
\
- (id)copyWithZone:(nullable NSZone *)zone{\
return self;\
}
#else // 非arc环境

#define SFSingleton_m(name)  +(instancetype)shared##name{ \
static id instance = nil; \
static dispatch_once_t onceToken;\
dispatch_once(&onceToken, ^{\
instance = [[self alloc] init];\
});\
return instance;\
}\
\
+ (instancetype)allocWithZone:(struct _NSZone *)zone {\
static id instance = nil;\
static dispatch_once_t onceToken;\
dispatch_once(&onceToken, ^{\
instance = [super allocWithZone:zone];\
});\
return instance;\
}\
\
+ (id)copyWithZone:(nullable NSZone *)zone{\
return self;\
}\
+ (oneway void)release {\
}\
\
+ (instancetype)autorelease {\
return self;\
}\
\
+ (instancetype)retain {\
return self;\
}\
\
+ (NSUInteger)retainCount {\
return 1;\
}
#endif


#endif /* SFFunc_h */
