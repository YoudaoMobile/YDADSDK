//
//  YD_SDK_VERSION    2.16.26
//  Created by lilu on 2021/1/18.
//  Copyright © 2021 Netease Youdao. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <WebKit/WebKit.h>

extern const CGFloat yd_kUniversalStarRatingScale;
extern const CGFloat yd_kStarRatingMaxValue;
extern const CGFloat yd_kStarRatingMinValue;
extern const NSTimeInterval yd_kDefaultRequiredSecondsForImpression;
extern NSString *const yd_kAdTitleKey;
extern NSString *const yd_kAdTextKey;
extern NSString *const yd_kAdIconImageKey;
extern NSString *const yd_kAdMainImageKey;
extern NSString *const yd_kAdCTATextKey;
extern NSString *const yd_kAdStarRatingKey;
extern NSString *const yd_kVideoConfigKey;
extern NSString *const yd_kVASTVideoKey;
extern NSString *const yd_kVideoKey;
extern NSString *const yd_kStyleNameKey;
extern NSString *const yd_kNativeVideoAdConfigKey;
extern NSString *const yd_kAdDAAIconImageKey;
extern NSString *const yd_kDAAIconImageName;
extern NSString *const yd_kDAAIconTapDestinationURL;
extern NSString *const yd_kImpressionTrackerURLsKey;
extern NSString *const yd_kDefaultActionURLKey;
extern NSString *const yd_kClickTrackerURLKey;
extern NSString *const yd_kCtaTrackerURLKey;
extern NSString *const yd_kAdYDEXTTextKey;
extern NSString *const yd_kLogEventRequestPropertiesKey;
extern NSString *const yd_kBrandAdTypeHeaderKey;
extern NSString *const yd_kDeeplinkURLKey;
extern NSString *const yd_kDeeplinkTrackerURLsKey;

UIInterfaceOrientation YDInterfaceOrientation(void);
UIWindow *YDKeyWindow(void);
CGFloat YDStatusBarHeight(void);
CGRect YDApplicationFrame(void);
CGRect YDScreenBounds(void);
CGSize YDScreenResolution(void);
CGFloat YDDeviceScaleFactor(void);
NSDictionary *YDDictionaryFromQueryString(NSString *query);
NSString *YDSHA1Digest(NSString *string);
BOOL YDViewIsVisible(UIView *view);
BOOL YDViewIntersectsParentWindowWithPercent(UIView *view, CGFloat percentVisible);
NSString *YDResourcePathForResource(NSString *resourceName);
NSArray *YDConvertStringArrayToURLArray(NSArray *strArray);

typedef void(^YDNativeAdBatchProviderHandler)(NSArray *responses,
                                              NSError *error);

typedef NS_ENUM(NSInteger, YDHostDomain){
    YDHostDomainDefault,  //默认域名gorgon
    YDHostDomainHongKong  //香港域名gorgon
};

@interface YDAdManager : NSObject
/// 广告请求host地址
@property (nonatomic, assign) YDHostDomain  hostDomain;
/// 广告请求超时时间，以秒为单位，默认10.0
@property (nonatomic, assign) NSTimeInterval  hostTimeoutInterval;
/// 广告请求是否允许下载资源，全局配置，默认YES
@property (nonatomic, assign) BOOL allowDownloadResource;
/// 允许获取时区参数,默认为YES
@property (nonatomic, assign) BOOL  isTimeZoneParamsEnabled;
/// 允许获取反作弊参数,默认为YES
@property (nonatomic, assign) BOOL  isAntiCheatingParamsEnabled;
/// 允许获取设备信息,默认为YES
@property (nonatomic, assign) BOOL  isDeviceParamsEnabled;
/// 全局 AAID 用于广告主归因
@property (nonatomic, copy) NSString *aaid;
/**
 * 是否允许 SDK 获取应用安装信息
 * 默认为YES
 */
@property (nonatomic, assign) BOOL checkAppsInfo;
/// 获取单例
+ (YDAdManager *)sharedInstance;
/// 获取广告前的准备工作，必须在request广告前先调用这个接口
- (void)prepareForLoadAd;
@end

@interface YDNativeAdUtils : NSObject
+ (BOOL)isDeeplinkURL:(NSURL *)URL;
@end

@interface YDIdentityProvider : NSObject
+ (NSString *)identifier;
+ (NSString *)obfuscatedIdentifier;
+ (BOOL)advertisingTrackingEnabled;
+ (NSString *)getCallBackUserIdentifier;
+ (void)storeCallBackUserIdentifier:(NSString *)callBackIdentifier;
@end

/// 广告点击信息
@interface YDNativeAdClickInfo : NSObject
/// 点击广告时点击位置相对于广告view的X坐标
@property (nonatomic, assign) CGFloat clkX;
/// 点击广告时点击位置相对于广告view的Y坐标
@property (nonatomic, assign) CGFloat clkY;
/// 广告view宽
@property (nonatomic, assign) CGFloat adWidth;
/// 广告view高
@property (nonatomic, assign) CGFloat adHeight;
@end

/// 微信小程序跳转字段信息
@interface YDLaunchWxMiniProgramInfo : NSObject
/// 微信小程序跳转字段所有字段字典
@property (nonatomic, strong) NSDictionary *wxMiniProgramDict;
@property (nonatomic, copy) NSString *appid;
@property (nonatomic, copy) NSString *originid;
@property (nonatomic, copy) NSString *path;
@end

@protocol YDNativeAdAdapter;
@protocol YDNativeAdDelegate;
@protocol YDNativeAdRenderer;
@protocol YDBrowserViewControllerBuilderDelegate;
@class YDAdConfiguration;
@class YDBrowserViewController;
@class YDNativeAdClickInfo;
@interface YDNativeAd : NSObject
@property (nonatomic) BOOL hasAttachedToView;
@property (nonatomic, weak) id<YDNativeAdDelegate> delegate;
@property (nonatomic, strong) id<YDBrowserViewControllerBuilderDelegate> browserViewControllerBuilderDelegate;
@property (nonatomic, readonly) NSDictionary *properties;
@property (nonatomic, readonly) id<YDNativeAdAdapter> adAdapter;
- (instancetype)initWithAdAdapter:(id<YDNativeAdAdapter>)adAdapter;
- (UIView *)retrieveAdViewWithError:(NSError **)error browserViewControllerBuilderDelegate:(id<YDBrowserViewControllerBuilderDelegate>)browserViewControllerBuilderDelegate;
- (void)playEndCardVideo;
- (void)startPreFetchVideo;
- (BOOL)verifyVideoInfoValid;
@property (nonatomic, assign) BOOL isBrand;
@property (nonatomic, assign) BOOL isEndCardVideo;
@property (nonatomic, assign) NSTimeInterval timeoutInterval;
/**
 品牌广告点击类型;
 取值为"0"为"跳转落地页";
 取值为"1"为"跳转视频内页";
 取值为"2"为"跳转deeplink";
 取值为"3"为"跳转小程序";
 */
@property (nonatomic, copy) NSString *brandClkType;

/// 微信小程序跳转相关字段
@property (nonatomic, strong) YDLaunchWxMiniProgramInfo *wxMiniProgramInfo;

/// 获取落地页URL
- (NSURL *)actualActionURL;

/// 获取落地页URL
/// @param clickInfo 点击信息
- (NSURL *)actualActionURLWithClickInfo:(YDNativeAdClickInfo *)clickInfo;

/// 广告点击上报接口
/// 若开发者自行渲染广告需要上报点击事件的时候调用此接口
- (void)trackAdClick;

/// 广告点击上报接口,同trackAdClick
/// @param clickInfo 点击信息
- (void)trackAdClickWithClickInfo:(YDNativeAdClickInfo *)clickInfo;

/// 广告展示上报接口
/// 若开发者自行渲染广告需要上报展示事件的时候调用此接口
- (void)trackAdImpression;

/// 广告打开deeplink上报接口
/// 若开发者自行渲染广告需要上报打开deeplink事件的时候调用此接口
/// @param deeplinkUrl 打开的deeplinkUrl
/// @param success 是否打开成功
- (void)trackAdDeeplinkUrl:(NSURL *)deeplinkUrl success:(BOOL)success;
/**
 广告打开微信小程序上报接口
 若开发者自行渲染广告需要上报打开微信小程序事件的时候调用此接口
 @param success 是否打开成功
 */
- (void)trackAdWxMiniProgramSuccess:(BOOL)success;
///构建信息流视频落地页vc
/// @param isPushed 是否是push操作
- (UIViewController *)buildNativeVideoVcWithIsPushed:(BOOL)isPushed;
@end

@interface YODAOPlayerViewController : UIViewController
@property (nonatomic) BOOL muted;
@end

@interface YDDefaultNativeVideoController  : UIViewController
@property (nonatomic) YODAOPlayerViewController *playerController;
@end

@interface YDNativeCache : NSObject
+ (instancetype)sharedCache;
- (BOOL)cachedDataExistsForKey:(NSString *)key;
- (NSData *)retrieveDataForKey:(NSString *)key;
- (NSURL *)retrieveDataUrlForKey:(NSString *)key;
- (void)storeData:(NSData *)data forKey:(NSString *)key;
- (void)removeAllDataFromCache;
- (void)setInMemoryCacheEnabled:(BOOL)enabled;
@end
@protocol YDNativeAdDelegate <NSObject>
@optional
- (void)willPresentModalForNativeAd:(YDNativeAd *)nativeAd;
- (void)didDismissModalForNativeAd:(YDNativeAd *)nativeAd;
- (void)willLeaveApplicationFromNativeAd:(YDNativeAd *)nativeAd;
- (void)videoWillPlayFromNativeAd:(YDNativeAd *)nativeAd;
- (void)videoWillCloseFromNativeAd:(YDNativeAd *)nativeAd;
- (void)videoWillShowEndCardViewFromNativeAd:(YDNativeAd *)nativeAd;
- (void)videoMutedButtonPressedFromNativeAd:(YDNativeAd *)nativeAd;
- (void)willStartPreFetchVideoForNativeAd:(YDNativeAd *)nativeAd;
- (void)readyToPlayVideoForNativeAd:(YDNativeAd *)nativeAd;
- (void)failPreFetchVideoForNativeAd:(YDNativeAd *)nativeAd;
- (void)videoPlayErrorForNativeAd:(YDNativeAd *)nativeAd;
/// 激励视频广告完成播放回调
/// @param isPlayDone 是否播放完成，若用户点击关闭按钮则返回NO，正常播放完成返回YES
/// @param nativeAd Ad
- (void)rewardVideoDidFinish:(BOOL)isPlayDone forNativeAd:(YDNativeAd *)nativeAd;
- (void)nativeAdWillLogImpression:(YDNativeAd *)nativeAd;
- (void)nativeAdDidClick:(YDNativeAd *)nativeAd;
@required
- (UIViewController *)viewControllerForPresentingModalView;
@end

@protocol YDNativeAdAdapterDelegate <NSObject>
@required
- (UIViewController *)viewControllerForPresentingModalView;
- (void)nativeAdWillPresentModalForAdapter:(id<YDNativeAdAdapter>)adapter;
- (void)nativeAdDidDismissModalForAdapter:(id<YDNativeAdAdapter>)adapter;
- (void)nativeAdWillLeaveApplicationFromAdapter:(id<YDNativeAdAdapter>)adapter;
@optional
- (void)nativeAdWillLogImpression:(id<YDNativeAdAdapter>)adAdapter;
- (void)nativeAdDidClick:(id<YDNativeAdAdapter>)adAdapter;
@end

@protocol YDNativeAdAdapter <NSObject>
@required
@property (nonatomic, readonly) NSDictionary *properties;
@property (nonatomic, readonly) NSURL *defaultActionURL;
@optional
- (void)displayContentForURL:(NSURL *)URL rootViewController:(UIViewController *)controller withBrowserController:(YDBrowserViewController *)browserController;
- (BOOL)enableThirdPartyClickTracking;
- (void)trackClick;
@property (nonatomic, weak) id<YDNativeAdAdapterDelegate> delegate;
- (void)willAttachToView:(UIView *)view;
- (void)displayContentForDAAIconTapWithBrowserController:(YDBrowserViewController *)browserController;
- (UIView *)privacyInformationIconView;
- (UIView *)mainMediaView;
@end

@class YDNativeAdRenderingImageLoader;
@protocol YDNativeAdRendering <NSObject>
@optional
- (UILabel *)nativeMainTextLabel;
- (UILabel *)nativeTitleTextLabel;
- (UIImageView *)nativeIconImageView;
- (UIImageView *)nativeMainImageView;
- (UIView *)nativeVideoView;
- (UILabel *)nativeCallToActionTextLabel;
- (UIImageView *)nativePrivacyInformationIconImageView;
- (NSMutableDictionary *)nativePropertyTextLabels;
- (NSMutableDictionary *)nativePropertyImageViews;
- (void)layoutStarRating:(NSNumber *)starRating;
/// 开屏广告新增，允许SDK对是否全屏广告做布局调整
- (void)layoutFullScreen:(BOOL)isFullScreen;
- (void)layoutCustomAssetsWithProperties:(NSDictionary *)customProperties imageLoader:(YDNativeAdRenderingImageLoader *)imageLoader;
+ (UINib *)nibForAd;
@end

@class YDNativeAdRendererImageHandler;
@interface YDNativeAdRenderingImageLoader : NSObject
- (instancetype)initWithImageHandler:(YDNativeAdRendererImageHandler *)imageHandler;
- (void)loadImageForURL:(NSURL *)url intoImageView:(UIImageView *)imageView;
@end


@class YDNativeAdRequest;
@class YDNativeAdRequestTargeting;

typedef void(^YDNativeAdRequestHandler)(YDNativeAdRequest *request,
                                        YDNativeAd *response,
                                        NSError *error);
@interface YDNativeAdRequest : NSObject
@property (nonatomic, strong) YDNativeAdRequestTargeting *targeting;
/// 广告网络请求超时时间，默认为[YDAdManager sharedInstance].hostTimeoutInterval
@property (nonatomic, assign) NSTimeInterval requestTimeout;
/// 允许请求广告时下载资源,默认为[YDAdManager sharedInstance].allowDownloadResource
@property (nonatomic, assign) BOOL allowDownloadResource;
+ (YDNativeAdRequest *)requestWithAdUnitIdentifier:(NSString *)identifier rendererConfigurations:(NSArray *)rendererConfigurations;
+ (YDNativeAdRequest *)requestWithAdUnitIdentifier:(NSString *)identifier rendererConfigurations:(NSArray *)rendererConfigurations adNet:(NSString *)adNet;
- (void)startWithCompletionHandler:(YDNativeAdRequestHandler)handler;
- (void)startWithAdSequence:(NSInteger)adSequence withCompletionHandler:(YDNativeAdRequestHandler)handler;
@end

@class YDNativeAdPreloadRequest, YDNativeAdRequestTargeting;
typedef void(^YDNativeAdPreloadRequestHandler)(YDNativeAdPreloadRequest *request,
                                        NSDictionary *response,
                                        NSError *error);
@interface YDNativeAdPreloadRequest : NSObject
@property (nonatomic, strong) YDNativeAdRequestTargeting *targeting;
+ (YDNativeAdPreloadRequest *)requestWithAdUnitIdentifier:(NSString *)identifier;

- (void)preloadWithCompletionHandler:(YDNativeAdPreloadRequestHandler)handler;
- (void)preloadWithAdSequence:(NSInteger)adSequence withCompletionHandler:(YDNativeAdPreloadRequestHandler)handler;
@end

// 开屏广告缓存request
@class YDSplashAdPreloadRequest, YDNativeAdRequestTargeting;
typedef void(^YDSplashAdPreloadRequestHandler)(YDSplashAdPreloadRequest *request, NSDictionary *response, NSError *error);
@interface YDSplashAdPreloadRequest : NSObject
@property (nonatomic, strong) YDNativeAdRequestTargeting *targeting;
+ (YDSplashAdPreloadRequest *)requestWithAdUnitIdentifier:(NSString *)identifier;
- (void)preloadWithCompletionHandler:(YDSplashAdPreloadRequestHandler)handler;
- (void)preloadWithAdSequence:(NSInteger)adSequence withCompletionHandler:(YDSplashAdPreloadRequestHandler)handler;
@end

//开屏广告相关
@class YDSplashAd, YDSplashAdRequest, YDNativeAdRequestTargeting;

typedef void(^YDSplashAdRequestHandler)(YDSplashAdRequest *request, YDSplashAd *response, NSError *error);

@interface YDSplashAdRequest : NSObject
@property (nonatomic, strong) YDNativeAdRequestTargeting *targeting;
/// 开屏广告请求超时时间，默认0.3s
@property (nonatomic, assign) NSTimeInterval requestTimeout;
+ (YDSplashAdRequest *)requestWithAdUnitIdentifier:(NSString *)identifier;
- (void)startWithCompletionHandler:(YDSplashAdRequestHandler)handler;
@end

@interface YDSplashAdRenderer : NSObject <YDNativeAdRenderer>
@property (nonatomic, assign) Class renderingViewClass;
@end

@class YDSplashAd, YDSplashAdRenderer;
@protocol YDSplashAdDelegate <NSObject>
- (void)splashAdDidLogImpression:(YDSplashAd *)splashAd;
- (void)splashAdDidClick:(YDSplashAd *)splashAd;
- (void)splashAdDidDismiss:(YDSplashAd *)splashAd;
@end

@interface YDSplashAd : NSObject
@property (nonatomic, strong) YDNativeAd *nativeAd;
/// 广告位id
@property (nonatomic, copy) NSString *placementId;
/// 点击交互类型参数，值为"1"表示摇一摇交互，值为"2"表示滑动交互，无值或无参数下发时，默认为普通点击交互类型;
@property (nonatomic, copy) NSString *clickType;
/// 点击前往文案
@property (nonatomic, copy) NSString *clkText;
/// 广告创意id
@property (nonatomic, copy) NSString *creativeId;
/// 是否全屏
@property (nonatomic, assign) BOOL fullScreen;
/// 是否可以全屏点击
@property (nonatomic, assign) BOOL fullScreenClick;
/// 是否是滑动交互类型广告
@property (nonatomic, assign) BOOL slideInteract;
/// 广告Id
@property (nonatomic, copy) NSString *adId;
/// 是否为效果广告占位符，效果广告占位符只包含weight和isEffectCarouselPos两个字段
@property (nonatomic, assign) BOOL isEffectCarouselPos;
/// 开屏形态，“0”：开屏回收，“1”：原生广告，”“：普通形态（即原有eadd接口desc字段）
@property (nonatomic, copy) NSString *uiStyle;
/// 是否是首刷广告
@property (nonatomic, assign) BOOL isFirstShot;
/// 是否支持摇一摇，1：是，2：否
@property (nonatomic, copy) NSString *shakable;
/// 开屏展示时间，单位为秒
@property (nonatomic, assign) NSInteger showInterval;
/// 轮播权重
@property (nonatomic, assign) NSInteger weight;
/// 开始结束时间单位毫秒
@property (nonatomic, assign) NSTimeInterval startTime;
@property (nonatomic, assign) NSTimeInterval endTime;
/// 最后修改时间
@property (nonatomic, assign) NSTimeInterval modTime;
/// 所有字段
@property (nonatomic, strong) NSDictionary *jsonDict;

@property (nonatomic, weak)  id<YDSplashAdDelegate> delegate;

@property (nonatomic, strong) YDSplashAdRenderer *render;
- (UIView *)renderAdView;

- (instancetype)initWithDict:(NSDictionary *)jsonDict;
/// 是否是今天的排期广告
- (BOOL)isTodayAdValid;
/// 是否已缓存全部素材
- (BOOL)isCached;
/// 是否是效果广告位占位
- (BOOL)isEffectCarousel;
/// 广告点击上报接口
- (void)trackSplashAdClick;
/// 广告展示上报接口
- (void)trackSplashAdImpression;
@end

@class YDSplashAd, YDSplashAdLoader, YDNativeAdRequestTargeting;

typedef void(^YDSplashAdLoaderHandler)(YDSplashAdLoader *request, YDSplashAd *response, NSError *error);

@interface YDSplashAdLoader : NSObject
@property (nonatomic, strong) YDNativeAdRequestTargeting *targeting;
@property (nonatomic, copy) NSString *adUnitIdentifier;
/// 开屏广告请求超时时间，默认0.3s
@property (nonatomic, assign) NSTimeInterval requestTimeout;

+ (YDSplashAdLoader *)loaderWithAdUnitIdentifier:(NSString *)identifier;
- (void)loadWithCompletionHandler:(YDSplashAdLoaderHandler)handler;
@end

@class YDSplashAdPreloader, YDNativeAdRequestTargeting;

typedef void(^YDSplashAdPreloaderHandler)(YDSplashAdPreloader *request, NSDictionary *response, NSError *error);

@interface YDSplashAdPreloader : NSObject
@property (nonatomic, strong) YDNativeAdRequestTargeting *targeting;
/// 广告网络请求超时时间，默认为[YDAdManager sharedInstance].hostTimeoutInterval
@property (nonatomic, assign) NSTimeInterval requestTimeout;
/// 允许4G网络缓存图片资源,默认为YES
@property (nonatomic, assign) BOOL allowDownloadImageResourceVia4G;
/// 允许4G网络缓存视频资源,默认为YES
@property (nonatomic, assign) BOOL allowDownloadVideoResourceVia4G;

+ (YDSplashAdPreloader *)loaderWithAdUnitIdentifier:(NSString *)identifier;
- (void)preloadWithCompletionHandler:(YDSplashAdPreloaderHandler)handler;
@end

@interface YDNativeAdBatchProvider : NSObject
/// 广告网络请求超时时间，默认为[YDAdManager sharedInstance].hostTimeoutInterval
@property (nonatomic, assign) NSTimeInterval requestTimeout;
/// 允许请求广告时下载资源,默认为[YDAdManager sharedInstance].allowDownloadResource
@property (nonatomic, assign) BOOL allowDownloadResource;
+ (YDNativeAdBatchProvider *)requestWithAdUnitIdentifier:(NSString *)identifier rendererConfigurations:(NSArray *)rendererConfigurations;
- (void)getAdsWithTargeting:(YDNativeAdRequestTargeting *)targeting withAmount:(NSInteger)amount afterComplete:(YDNativeAdBatchProviderHandler)customHandler;
- (void)cleanRecievedIds;
@end


@protocol YDNativeAdAdapter;
@protocol YDNativeAdRendererSettings;
@interface YDNativeAdRendererConfiguration : NSObject

/// The settings that inform the ad renderer about how it should render the ad.
@property (nonatomic, strong) id<YDNativeAdRendererSettings> rendererSettings;

/// The renderer class used to render supported custom events.
@property (nonatomic, assign) Class rendererClass;

/// An array of custom event class names (as strings) that the renderClass can render.
@property (nonatomic, strong) NSArray *supportedCustomEvents;
/// The styleName setted on the app web-site used to be selected to render the ad.
@property (nonatomic, readwrite, strong) NSString *styleName;
@end

typedef CGSize (^YDNativeViewSizeHandler)(CGFloat maximumWidth);
@protocol YDNativeAdRenderer <NSObject>
@required
+ (YDNativeAdRendererConfiguration *)rendererConfigurationWithRendererSettings:(id<YDNativeAdRendererSettings>)rendererSettings;
- (instancetype)initWithRendererSettings:(id<YDNativeAdRendererSettings>)rendererSettings;
- (UIView *)retrieveViewWithAdapter:(id<YDNativeAdAdapter>)adapter error:(NSError **)error;
@optional
@property (nonatomic, readonly) YDNativeViewSizeHandler viewSizeHandler;
- (void)adViewWillMoveToSuperview:(UIView *)superview;
- (void)nativeAdTapped;
@end

@protocol YDNativeAdRendererSettings <NSObject>
@optional
@property (nonatomic, readwrite, strong) NSString* styleName;
@property (nonatomic, readwrite, copy) YDNativeViewSizeHandler viewSizeHandler;
@end

@interface YDStaticNativeAdRendererSettings : NSObject <YDNativeAdRendererSettings>
@property (nonatomic, assign) Class renderingViewClass;
@property (nonatomic, readwrite, copy) YDNativeViewSizeHandler viewSizeHandler;
@end

@interface YODAONativeVideoAdRendererSettings : NSObject <YDNativeAdRendererSettings>
@property (nonatomic, assign) Class renderingViewClass;
@property (nonatomic, readwrite, copy) YDNativeViewSizeHandler viewSizeHandler;
/// 是否在wifi网络下自动播放信息流视频广告,默认为YES
@property (nonatomic, assign) BOOL autoPlay;
/// 是否显示激励视频广告的关闭按钮,默认为NO
@property (nonatomic, assign) BOOL showCloseBtnForRewardVideo;
@end

//@class YDStaticNativeAdRendererSettings;
@interface YDStaticNativeAdRenderer : NSObject <YDNativeAdRenderer>
@property (nonatomic, readonly) YDNativeViewSizeHandler viewSizeHandler;
+ (YDNativeAdRendererConfiguration *)rendererConfigurationWithRendererSettings:(id<YDNativeAdRendererSettings>)rendererSettings andStyleName:(NSString*) styleName;
@end

@interface YODAONativeVideoAdRenderer : NSObject
@property (nonatomic, readonly) YDNativeViewSizeHandler viewSizeHandler;
+ (YDNativeAdRendererConfiguration *)rendererConfigurationWithRendererSettings:(id<YDNativeAdRendererSettings>)rendererSettings andStyleName:(NSString*) styleName;
@end

@class CLLocation;
@interface YDNativeAdRequestTargeting : NSObject
+ (YDNativeAdRequestTargeting *)targeting;
@property (nonatomic, copy) NSString *keywords;
@property (nonatomic, copy) CLLocation *location;
@property (nonatomic, strong) NSSet *desiredAssets;
/// 是否上报最近展示的广告CreativeIds,默认为NO
@property (nonatomic, assign) BOOL uploadLastCreativeIds;
/// 是否支持个性化推荐广告,默认为YES
@property (nonatomic, assign) BOOL supportTargetedAd;
/// 开屏广告logo高度
@property (nonatomic, assign) CGFloat splashLogoHeight;
/// CAID 用于广告主归因
@property (nonatomic, copy) NSString *caid;
/// AAID 用于广告主归因
@property (nonatomic, copy) NSString *aaid;
/// 额外参数
@property (nonatomic, strong)  NSMutableDictionary *extraParams;
@end

@class YDBrowserViewController;
@protocol YDBrowserViewControllerBuilderDelegate <NSObject>
- (YDBrowserViewController*) buildBrowserViewControllerWithYDNativeAd:(YDNativeAd *)ad;
@end

@protocol YDBrowserControllerDelegate;
@interface YDBrowserViewController : UIViewController
@property (nonatomic, copy) NSURL *landingPageURL;
@property (nonatomic, copy) NSString *HTMLString;
@property (nonatomic, weak) id<YDBrowserControllerDelegate> delegate;
@end

@interface YDConvTracker : NSObject
+ (instancetype) convTrackerForAd:(YDNativeAd *)ad;
- (void) startLoadAdWithWebView:(WKWebView *)webView;
- (void) finishLoadAdWithWebView:(WKWebView *)webView;
- (void) sendTrackerData:(NSURLRequest *)request;
- (void) closeWebView;
@end

@protocol YDBrowserControllerDelegate <NSObject>
- (void)dismissBrowserController:(YDBrowserViewController *)browserController animated:(BOOL)animated;
@end
@class YDNativeAdRequestTargeting;
@protocol YDTableViewAdPlacerDelegate;
@protocol YDBrowserViewControllerBuilderDelegate;

@interface YDAdPositioning : NSObject <NSCopying>
@property (nonatomic, assign) NSUInteger repeatingInterval;
@property (nonatomic, strong, readonly) NSMutableOrderedSet *fixedPositions;
@end

@interface YDClientAdPositioning : YDAdPositioning
+ (instancetype)positioning;
- (void)addFixedIndexPath:(NSIndexPath *)indexPath;
- (void)enableRepeatingPositionsWithInterval:(NSUInteger)interval;
@end

@interface YDServerAdPositioning : YDAdPositioning
+ (instancetype)positioning;
@end

@interface YDTableViewAdPlacer : NSObject
@property (nonatomic, weak) id<YDTableViewAdPlacerDelegate> delegate;
+ (instancetype)placerWithTableView:(UITableView *)tableView viewController:(UIViewController *)controller rendererConfigurations:(NSArray *)rendererConfigurations withBrowserViewControllerBuilderDelegate:(id<YDBrowserViewControllerBuilderDelegate>)browserViewControllerBuilderDelegate;
+ (instancetype)placerWithTableView:(UITableView *)tableView viewController:(UIViewController *)controller adPositioning:(YDAdPositioning *)positioning rendererConfigurations:(NSArray *)rendererConfigurations withBrowserViewControllerBuilderDelegate:(id<YDBrowserViewControllerBuilderDelegate>)browserViewControllerBuilderDelegate;
- (void)loadAdsForAdUnitID:(NSString *)adUnitID;
- (void)loadAdsForAdUnitID:(NSString *)adUnitID targeting:(YDNativeAdRequestTargeting *)targeting;
- (void)loadAdsForAdUnitID:(NSString *)adUnitID targeting:(YDNativeAdRequestTargeting *)targeting adNet:(NSString *)adNet;
@end

@interface UITableView (YDTableViewAdPlacer)
- (void)yd_setAdPlacer:(YDTableViewAdPlacer *)placer;
- (YDTableViewAdPlacer *)yd_adPlacer;
- (void)yd_setDataSource:(id<UITableViewDataSource>)dataSource;
- (id<UITableViewDataSource>)yd_dataSource;
- (void)yd_setDelegate:(id<UITableViewDelegate>)delegate;
- (id<UITableViewDelegate>)yd_delegate;
- (void)yd_beginUpdates;
- (void)yd_endUpdates;
- (void)yd_reloadData;
- (void)yd_insertRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)yd_deleteRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)yd_reloadRowsAtIndexPaths:(NSArray *)indexPaths withRowAnimation:(UITableViewRowAnimation)animation;
- (void)yd_moveRowAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath;
- (void)yd_insertSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)yd_deleteSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)yd_reloadSections:(NSIndexSet *)sections withRowAnimation:(UITableViewRowAnimation)animation;
- (void)yd_moveSection:(NSInteger)section toSection:(NSInteger)newSection;
- (UITableViewCell *)yd_cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (id)yd_dequeueReusableCellWithIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;
- (void)yd_deselectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;
- (NSIndexPath *)yd_indexPathForCell:(UITableViewCell *)cell;
- (NSIndexPath *)yd_indexPathForRowAtPoint:(CGPoint)point;
- (NSIndexPath *)yd_indexPathForSelectedRow;
- (NSArray *)yd_indexPathsForRowsInRect:(CGRect)rect;
- (NSArray *)yd_indexPathsForSelectedRows;
- (NSArray *)yd_indexPathsForVisibleRows;
- (CGRect)yd_rectForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)yd_scrollToRowAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UITableViewScrollPosition)scrollPosition animated:(BOOL)animated;
- (void)yd_selectRowAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UITableViewScrollPosition)scrollPosition;
- (NSArray *)yd_visibleCells;
@end

@protocol YDTableViewAdPlacerDelegate <NSObject>
@optional
-(void)nativeAdWillPresentModalForTableViewAdPlacer:(YDTableViewAdPlacer *)placer;
-(void)nativeAdDidDismissModalForTableViewAdPlacer:(YDTableViewAdPlacer *)placer;
-(void)nativeAdWillLeaveApplicationFromTableViewAdPlacer:(YDTableViewAdPlacer *)placer;
@end

@protocol YDCollectionViewAdPlacerDelegate;

@interface YDCollectionViewAdPlacer : NSObject
@property (nonatomic, weak) id<YDCollectionViewAdPlacerDelegate> delegate;
+ (instancetype)placerWithCollectionView:(UICollectionView *)collectionView viewController:(UIViewController *)controller rendererConfigurations:(NSArray *)rendererConfigurations  withBrowserViewControllerBuilderDelegate:(id<YDBrowserViewControllerBuilderDelegate>)browserViewControllerBuilderDelegate;
+ (instancetype)placerWithCollectionView:(UICollectionView *)collectionView viewController:(UIViewController *)controller adPositioning:(YDAdPositioning *)positioning rendererConfigurations:(NSArray *)rendererConfigurations  withBrowserViewControllerBuilderDelegate:(id<YDBrowserViewControllerBuilderDelegate>)browserViewControllerBuilderDelegate;
- (void)loadAdsForAdUnitID:(NSString *)adUnitID;
- (void)loadAdsForAdUnitID:(NSString *)adUnitID targeting:(YDNativeAdRequestTargeting *)targeting;
- (void)loadAdsForAdUnitID:(NSString *)adUnitID targeting:(YDNativeAdRequestTargeting *)targeting adNet:(NSString *)adNet;
@end

@interface UICollectionView (YDCollectionViewAdPlacer)
- (void)yd_setAdPlacer:(YDCollectionViewAdPlacer *)placer;
- (YDCollectionViewAdPlacer *)yd_adPlacer;
- (void)yd_setDataSource:(id<UICollectionViewDataSource>)dataSource;
- (id<UICollectionViewDataSource>)yd_dataSource;
- (void)yd_setDelegate:(id<UICollectionViewDelegate>)delegate;
- (id<UICollectionViewDelegate>)yd_delegate;
- (void)yd_reloadData;
- (void)yd_insertItemsAtIndexPaths:(NSArray *)indexPaths;
- (void)yd_deleteItemsAtIndexPaths:(NSArray *)indexPaths;
- (void)yd_reloadItemsAtIndexPaths:(NSArray *)indexPaths;
- (void)yd_moveItemAtIndexPath:(NSIndexPath *)indexPath toIndexPath:(NSIndexPath *)newIndexPath;
- (void)yd_insertSections:(NSIndexSet *)sections;
- (void)yd_deleteSections:(NSIndexSet *)sections;
- (void)yd_reloadSections:(NSIndexSet *)sections;
- (void)yd_moveSection:(NSInteger)section toSection:(NSInteger)newSection;
- (UICollectionViewCell *)yd_cellForItemAtIndexPath:(NSIndexPath *)indexPath;
- (id)yd_dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath*)indexPath;
- (void)yd_deselectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;
- (NSIndexPath *)yd_indexPathForCell:(UICollectionViewCell *)cell;
- (NSIndexPath *)yd_indexPathForItemAtPoint:(CGPoint)point;
- (NSArray *)yd_indexPathsForSelectedItems;
- (NSArray *)yd_indexPathsForVisibleItems;
- (UICollectionViewLayoutAttributes *)yd_layoutAttributesForItemAtIndexPath:(NSIndexPath *)indexPath;
- (void)yd_scrollToItemAtIndexPath:(NSIndexPath *)indexPath atScrollPosition:(UICollectionViewScrollPosition)scrollPosition animated:(BOOL)animated;
- (void)yd_selectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated scrollPosition:(UICollectionViewScrollPosition)scrollPosition;
- (NSArray *)yd_visibleCells;
@end

@protocol YDCollectionViewAdPlacerDelegate <NSObject>
@optional
-(void)nativeAdWillPresentModalForCollectionViewAdPlacer:(YDCollectionViewAdPlacer *)placer;
-(void)nativeAdDidDismissModalForCollectionViewAdPlacer:(YDCollectionViewAdPlacer *)placer;
-(void)nativeAdWillLeaveApplicationFromCollectionViewAdPlacer:(YDCollectionViewAdPlacer *)placer;
@end

@class YDNativeCustomEvent;

@protocol YDNativeCustomEventDelegate <NSObject>
- (void)nativeCustomEvent:(YDNativeCustomEvent *)event didLoadAd:(YDNativeAd *)adObject;
- (void)nativeCustomEvent:(YDNativeCustomEvent *)event didFailToLoadAdWithError:(NSError *)error;
@end

@interface YDNativeCustomEvent : NSObject
- (void)requestAdWithCustomEventInfo:(NSDictionary *)info;
- (void)precacheImagesWithURLs:(NSArray *)imageURLs completionBlock:(void (^)(NSArray *errors))completionBlock;
@property (nonatomic, weak) id<YDNativeCustomEventDelegate> delegate;
@end

@interface YDAdBrowserConversionTracker : NSObject
typedef NS_ENUM(int, collectType){
    yd_adRequest = 0,
    yd_adRequestSuc = 1,
    yd_adRequestFail = 2,
    yd_adImpTrack = 3,
    yd_adClkTrack = 4,
};
@property (nonatomic, copy) NSString *url;
@property (nonatomic, copy) NSString *title;
@property (nonatomic, copy) NSString *creativeId;
@property (nonatomic, copy) NSString *slotId;
@property (nonatomic, copy) NSString *thirdSlotId;
@property (nonatomic, copy) NSString *idfa;
@property (nonatomic, assign) NSInteger errorCode;
@property (nonatomic, copy) NSString *errorMessage;
@property (nonatomic, copy) NSString *thirdName;
@property (nonatomic, assign) long seq;
@property (nonatomic, copy) NSString *formData;
@property (nonatomic, assign) NSTimeInterval hoverTime;
@property (nonatomic, copy) NSString *bidId;
@property (nonatomic, assign) NSTimeInterval loadingTime;
@property (nonatomic, assign) NSTimeInterval prepareTime;
@property (nonatomic, assign) NSTimeInterval startProgressTime;
- (id)initWithSlotId:(NSString *)slotId title:(NSString *)title thirdSlotId:(NSString *)thirdSlotId;
- (id)initWithCid:(NSString *)cid;
- (void) sendCollectDataWithType:(int)collectType;
- (void) sendConversionData;
- (void) sendVideoConversionDataType:(int)type pd:(int)pdTime dura:(int)duraTime videoUrl:(NSURL *)url ld:(int)ld full:(int)full;
@end

@interface YDAdTestMode : NSObject
+ (BOOL)isTesting;
+ (void)turnOn;
+ (void)turnOff;
+ (void)useEncryption;
+ (void)disableEncryption;
@end

typedef enum
{
    YDLogLevelAll = 0,
    YDLogLevelTrace = 10,
    YDLogLevelDebug = 20,
    YDLogLevelInfo = 30,
    YDLogLevelWarn = 40,
    YDLogLevelError = 50,
    YDLogLevelFatal = 60,
    YDLogLevelOff = 70
} YDLogLevel;

YDLogLevel YDLogGetLevel(void);
void YDLogSetLevel(YDLogLevel level);
void _YDLogTrace(NSString *format, ...);
void _YDLogDebug(NSString *format, ...);
void _YDLogInfo(NSString *format, ...);
void _YDLogWarn(NSString *format, ...);
void _YDLogError(NSString *format, ...);
void _YDLogFatal(NSString *format, ...);
#if YD_DEBUG_MODE && !SPECS

#define YDLogTrace(...) _YDLogTrace(__VA_ARGS__)
#define YDLogDebug(...) _YDLogDebug(__VA_ARGS__)
#define YDLogInfo(...) _YDLogInfo(__VA_ARGS__)
#define YDLogWarn(...) _YDLogWarn(__VA_ARGS__)
#define YDLogError(...) _YDLogError(__VA_ARGS__)
#define YDLogFatal(...) _YDLogFatal(__VA_ARGS__)

#else

#define YDLogTrace(...) {}
#define YDLogDebug(...) {}
#define YDLogInfo(...) {}
#define YDLogWarn(...) {}
#define YDLogError(...) {}
#define YDLogFatal(...) {}

#endif

typedef enum YDNativeAdErrorCode {
    YDNativeAdErrorUnknown = -1,
    YDNativeAdErrorHTTPError = -1000,
    YDNativeAdErrorInvalidServerResponse = -1001,
    YDNativeAdErrorNoInventory = -1002,
    YDNativeAdErrorImageDownloadFailed = -1003,
    YDNativeAdErrorAdUnitWarmingUp = -1004,
    YDNativeAdErrorVASTParsingFailed = -1005,
    YDNativeAdErrorVideoConfigInvalid = -1006,
    YDNativeAdErrorFacebookAdError = -1007,
    YDNativeAdErrorContentDisplayError = -1100,
    YDNativeAdErrorRenderError = -1200
} YDNativeAdErrorCode;

extern NSString * const YodaoNativeAdsSDKDomain;

NSError *YDNativeAdNSErrorForInvalidAdServerResponse(NSString *reason);
NSError *YDNativeAdNSErrorForAdUnitWarmingUp();
NSError *YDNativeAdNSErrorForNoInventory();
NSError *YDNativeAdNSErrorForNetworkConnectionError();
NSError *YDNativeAdNSErrorForInvalidImageURL();
NSError *YDNativeAdNSErrorForImageDownloadFailure();
NSError *YDNativeAdNSErrorForContentDisplayErrorMissingRootController();
NSError *YDNativeAdNSErrorForContentDisplayErrorInvalidURL();
NSError *YDNativeAdNSErrorForVASTParsingFailure();
NSError *YDNativeAdNSErrorForVideoConfigInvalid();
NSError *YDNativeAdNSErrorForRenderValueTypeError();
NSError *YDNativeAdNSErrorForFacebookAdError(NSString *fbErrorDesc);
