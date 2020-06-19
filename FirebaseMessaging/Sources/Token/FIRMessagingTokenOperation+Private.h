/*
 * Copyright 2019 Google
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#import "FIRMessagingTokenOperation.h"

#import "FIRMessagingUtilities.h"

NS_ASSUME_NONNULL_BEGIN

@interface FIRMessagingTokenOperation (Private)

@property(atomic, strong) NSURLSessionDataTask *dataTask;
@property(readonly, strong)
    NSMutableArray<FIRMessagingTokenOperationCompletion> *completionHandlers;


+ (NSURLSession *)sharedURLSession;

#pragma mark - Initialization
- (instancetype)initWithAction:(FIRMessagingTokenAction)action
           forAuthorizedEntity:(nullable NSString *)authorizedEntity
                         scope:(NSString *)scope
                       options:(nullable NSDictionary<NSString *, NSString *> *)options
            checkinPreferences:(FIRMessagingCheckinPreferences *)checkinPreferences
                    instanceID:(NSString *)instanceID;

#pragma mark - Request Construction
+ (NSMutableArray<NSURLQueryItem *> *)standardQueryItemsWithDeviceID:(NSString *)deviceID
                                                                          scope:(NSString *)scope;
- (NSMutableURLRequest *)tokenRequest;

#pragma mark - HTTP Headers
/**
 *  Given a valid checkin preferences object, it will return a string that can be used
 *  in the "Authorization" HTTP header to authenticate this request.
 *
 *  @param checkin The valid checkin preferences object, with a deviceID and secretToken.
 */
+ (NSString *)HTTPAuthHeaderFromCheckin:(FIRMessagingCheckinPreferences *)checkin;

#pragma mark - Result
- (void)finishWithResult:(FIRMessagingTokenOperationResult)result
                   token:(nullable NSString *)token
                   error:(nullable NSError *)error;

#pragma mark - Methods to override
- (void)performTokenOperation;

@end

NS_ASSUME_NONNULL_END