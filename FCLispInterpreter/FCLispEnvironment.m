//
//  FCLispEnvironment.m
//  FCLispInterpreter
//
//  Created by Almer Lucke on 10/1/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#import "FCLispEnvironment.h"
#import "FCLispSymbol.h"
#import "FCLispObject.h"
#import "FCLispScopeStack.h"


/**
 *  Private interface
 */
@interface FCLispEnvironment ()
{
    /**
     *  Mutable dictionary containing all symbols in environment
     */
    NSMutableDictionary *_symbols;
    
    /**
     *  Creation of symbols MUST be thread safe, so we perform the creation of symbols 
     *  in serial on a dedicated queue
     */
    dispatch_queue_t _symbolCreationQueue;
    
    /**
     *  Global scope dictionary, this SHOULD be the first entry into any scope stack
     */
    NSMutableDictionary *_globalScope;
    
    /**
     *  Default (main thread) scope stack
     */
    FCLispScopeStack *_scopeStack;
}
@end



@implementation FCLispEnvironment

#pragma mark - Singleton

+ (FCLispEnvironment *)defaultEnvironment
{
    static FCLispEnvironment *sDefaultEnvironment;
    static dispatch_once_t sDispatchOnce;
    
    dispatch_once(&sDispatchOnce, ^{
        sDefaultEnvironment = [[FCLispEnvironment alloc] init];
    });
    
    return sDefaultEnvironment;
}

- (void)initialize
{
    // symbol dictionary
    _symbols = [NSMutableDictionary dictionary];
    
    // create serial symbol creation queue
    _symbolCreationQueue = dispatch_queue_create("kFCLispEnvironmentSymbolQueue", DISPATCH_QUEUE_SERIAL);
    
    // create global scope
    _globalScope = [NSMutableDictionary dictionary];
    
    // create main thread scope stack
    _scopeStack = [FCLispScopeStack scopeStackWithScope:_globalScope];
}

- (id)init
{
    if ((self = [super init])) {
        [self initialize];
    }
    
    return self;
}


#pragma mark - GenSym

- (FCLispSymbol *)genSym:(NSString *)name
{
    // symbols should be uppercase
    NSString *uppercaseName = [name uppercaseString];
    
    // we want to assign to this variable from inside block, so use __block indicator
    __block FCLispSymbol *symbol = nil;
    
    // perform the creation of the symbol on a dedicated serial queue (making sure we don't create the symbol twice from
    // different threads)
    dispatch_sync(_symbolCreationQueue, ^{
        // first get symbol from cache
        symbol = [_symbols objectForKey:uppercaseName];
        
        if (!symbol) {
            // not cached so create a new symbol
            symbol = [[FCLispSymbol alloc] initWithName:uppercaseName];
            [_symbols setObject:symbol forKey:uppercaseName];
        }
    });
    
    return symbol;
}

+ (FCLispSymbol *)genSym:(NSString *)name
{
    return [[self defaultEnvironment] genSym:name];
}


#pragma mark - Register

+ (void)registerClass:(Class)theClass
{
    if ([theClass isSubclassOfClass:[FCLispObject class]]) {
        [theClass addGlobalBindingsToEnvironment:[self defaultEnvironment]];
    }
}


#pragma mark - Scope

- (FCLispScopeStack *)defaultScopeStack
{
    return _scopeStack;
}

+ (FCLispScopeStack *)defaultScopeStack
{
    return [[self defaultEnvironment] defaultScopeStack];
}

- (NSMutableDictionary *)globalScope
{
    return _globalScope;
}

+ (NSMutableDictionary *)globalScope
{
    return [[self defaultEnvironment] globalScope];
}

@end
