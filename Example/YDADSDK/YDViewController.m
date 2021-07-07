//
//  YDViewController.m
//  YDADSDK
//
//  Created by buptlilu on 03/27/2020.
//  Copyright (c) 2020 buptlilu. All rights reserved.
//

#import "YDViewController.h"
#import <YDADSDK/YDSDKHeader.h>

@interface YDViewController ()

@end

@implementation YDViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    NSLog(@"%@", [YDNativeAd class]);
    
    UIImage *image = [UIImage imageNamed:YDResourcePathForResource(@"YDPlayer_big_play_btn")];
    NSLog(@"bundle####  image:%@", image);
    NSBundle *resourceBundle;
    NSBundle *bundle = [NSBundle mainBundle];
    NSString *path = [[NSBundle bundleForClass:[self class]] pathForResource:@"YDADSDK.framework/YDResource" ofType:@"bundle"];
    NSBundle *bundle2 = [NSBundle bundleWithIdentifier:@"com.youdao.YDADSDK"];
    NSLog(@"bundle####  bundle:%@", bundle);
    NSLog(@"bundle####  bundle2:%@", bundle2);
    image = [UIImage imageNamed:YDResourcePathForResource(@"YDPlayer_big_play_btn") inBundle:bundle2 compatibleWithTraitCollection:nil];
    NSLog(@"bundle####  image2:%@", image);
    resourceBundle = [NSBundle bundleWithPath:[[NSBundle mainBundle] pathForResource:@"YDADSDK.framework/YDResource" ofType:@"bundle"]];
    NSLog(@"bundle####  resourceBundle:%@", resourceBundle.resourcePath);
    
    NSString *bundlePath = [[NSBundle bundleForClass:[self class]].resourcePath
                                    stringByAppendingPathComponent:@"/YDResource.bundle"];
    NSLog(@"bundle####  bundlePath:%@", bundlePath);
    NSBundle *resource_bundle = [NSBundle bundleWithPath:bundlePath];
    NSLog(@"bundle####  resource_bundle:%@", resource_bundle);
    image = [UIImage imageNamed:@"YDPlayer_big_play_btn" inBundle:resource_bundle compatibleWithTraitCollection:nil];
    NSLog(@"bundle####  image3:%@", image);
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
