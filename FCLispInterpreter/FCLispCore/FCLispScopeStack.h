//
//  FCLispScopeStack.h
//  FCLispInterpreter
//
//  Created by Almer Lucke on 10/1/13.
//  Copyright (c) 2013 Farcoding. All rights reserved.
//

#import <Foundation/Foundation.h>


@class FCLispObject;
@class FCLispSymbol;


/**
 *  Push and pop scopes onto the stack.
 *  Variable bindings are looked up through the scope stack.
 *  Each scope is represented by a NSDictionary, where the key is the symbol name and the value is the binding.
 *  Each thread MUST create a new scope stack and functions evaluated on that thread SHOULD use the corresponding stack.
 */
@interface FCLispScopeStack : NSObject <NSCopying, NSCoding>

/**
 *  Initialize scope stack with an initial scope
 *
 *  @param scope NSMutableDictionary representing the scope
 *
 *  @return FSLispScopeStack object
 */
- (id)initWithScope:(NSMutableDictionary *)scope;

/**
 *  Convenience method to create a new scope stack with an empty first scope
 *
 *  @return FCLispScopeStack object
 */
+ (FCLispScopeStack *)scopeStack;

/**
 *  Convenience method to create a new scope stack with an initial scope
 *
 *  @param scope NSMutableDictionary representing the scope
 *
 *  @return FCLispScopeStack object
 */
+ (FCLispScopeStack *)scopeStackWithScope:(NSMutableDictionary *)scope;

/**
 *  Push an scope on the stack
 *
 *  @param scope If nil a new scope is created and pushed otherwise the give scope is pushed
 */
- (void)pushScope:(NSMutableDictionary *)scope;

/**
 *  Push an other scope stack on top of this scope stack
 *
 *  @param scopeStack
 */
- (void)pushScopeStack:(FCLispScopeStack *)scopeStack;

/**
 *  Pop a scope
 *
 *  @return NSMutableDictionary object representing the popped scope
 */
- (NSMutableDictionary *)popScope;

/**
 *  Pop the scopes in scopeStack from this scope
 *
 *  @param scopeStack
 */
- (void)popScopeStack:(FCLispScopeStack *)scopeStack;

/**
 *  Get current binding for symbol
 *
 *  @param symbol FCLispSymbol object
 *
 *  @return current symbol binding (nil if no binding)
 */
- (FCLispObject *)bindingForSymbol:(FCLispSymbol *)symbol;

/**
 *  Update or create current binding for symbol (search in all scopes)
 *  If binding is not found, create a new binding in the top scope
 *
 *  @param binding FCLispObject value
 *  @param symbol  FCLispSymbol object to bind to
 */
- (void)setBinding:(FCLispObject *)binding forSymbol:(FCLispSymbol *)symbol;

/**
 *  Add binding for symbol in top scope
 *  If the binding is already in top scope, update its value
 *
 *  @param binding FCLispObject value
 *  @param symbol  FCLispSymbol object to bind to
 */
- (void)addBinding:(FCLispObject *)binding forSymbol:(FCLispSymbol *)symbol;

@end