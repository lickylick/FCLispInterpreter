//
//  FCLispBuildinFunction.h
//  Lisp
//
//  Created by aFrogleap on 12/12/12.
//  Copyright (c) 2012 Farcoding. All rights reserved.
//

#import "FCLispFunction.h"

@class FCLispCons;
@class FCLispScopeStack;
@class FCLispSymbol;


/**
 *  Buildin Lisp Function
 */
@interface FCLispBuildinFunction : FCLispFunction

/**
 *  Can be set with a setf value
 */
@property (nonatomic) BOOL canBeSet;

/**
 *  Selector to handle function call
 */
@property (nonatomic) SEL selector;

/**
 *  Target on which to call selector
 */
@property (nonatomic, strong) id target;

/**
 *  Optional documentation about the use of this build in function.
 *  Arguments and return value.
 */
@property (nonatomic, copy) NSString *documentation;

/**
 *  Weak reference to symbol to which this function is assigned.
 *  We need this to encode/decode buildin function objects.
 */
@property (nonatomic, weak) FCLispSymbol *symbol;


/**
 *  Initialize buildin function
 *
 *  @param selector Actual method that is performed
 *  @param target   The target on which the selector is performed
 *  @param evalArgs Do we need to evaluate args
 *  @param canBeSet Is setf-able
 *
 *  @return Initialized FCLispBuildinFunction object
 */
- (id)initWithSelector:(SEL)selector
                target:(id)target
              evalArgs:(BOOL)evalArgs
              canBeSet:(BOOL)canBeSet;


/**
 *  Create buildin function, evalArgs = YES, canBeSet = NO
 *
 *  @param selector Actual method that is performed
 *  @param target   The target on which the selector is performed
 *
 *  @return FCLispBuildinFunction object
 */
+ (FCLispBuildinFunction *)functionWithSelector:(SEL)selector
                                         target:(id)target;

/**
 *  Create buildin function, canBeSet = NO
 *
 *  @param selector Actual method that is performed
 *  @param target   The target on which the selector is performed
 *  @param evalArgs Do we need to evaluate args
 *
 *  @return FCLispBuildinFunction object
 */
+ (FCLispBuildinFunction *)functionWithSelector:(SEL)selector
                                         target:(id)target
                                       evalArgs:(BOOL)evalArgs;

/**
 *  Create buildin function
 *
 *  @param selector Actual method that is performed
 *  @param target   The target on which the selector is performed
 *  @param evalArgs Do we need to evaluate args
 *  @param canBeSet Is setf-able
 *
 *  @return FCLispBuildinFunction object
 */
+ (FCLispBuildinFunction *)functionWithSelector:(SEL)selector
                                         target:(id)target
                                       evalArgs:(BOOL)evalArgs
                                       canBeSet:(BOOL)canBeSet;

/**
 *  Setf eval
 *
 *  @param args       FCLispCons argument list
 *  @param value      Setf value
 *  @param scopeStack FCLispScopeStack symbol scope stack
 *
 *  @return FCLispObject
 */
- (FCLispObject *)eval:(FCLispCons *)args value:(id)value scopeStack:(FCLispScopeStack *)scopeStack;

@end
