//
//  LetterAnimationLabel.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#ifndef __Novelio__LetterAnimationLabel__
#define __Novelio__LetterAnimationLabel__
#include <vector>

#include "cocos2d.h"
//#include "GameLabelProtocol.h"
#include "RubyLabel.h"

USING_NS_CC;


/* --------------------------------------------------------------------------*/
/**
* @brief アニメーション用ラベル。ルビ対応
*/
/* ----------------------------------------------------------------------------*/
class AnimationLabel : public RubyLabel/*, GameLabelProtocol*/{
public:
    AnimationLabel();
    ~AnimationLabel();
    static AnimationLabel * createWithTTF(const std::string& text, const std::string& fontFile,
                                     float fontSize, float rubyfontSize = 0,
                                     const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
                                     TextVAlignment vAlignment = TextVAlignment::TOP);
    

protected:
    std::function<void(void)> onLineEnds;
    std::function<void(void)> onParagraphEnds;
    std::function<void(void)> onEnds;
    
    bool isRunningFlg;
    bool isPausingFlg;
    
    std::function<cocos2d::FiniteTimeAction*(Sprite*, int, int)> makeAnimation;
    
public:
    void showAll();
    void clear();
    void run();
    void stop();
    void pause();
    void restart();

//    void clearText();
//    void setText(const std::string &text);
//    void addText(std::string text);
//    void setTexts(std::vector<std::string> texts);

    bool isRunning(void);
    bool isPausing(void);
    
    void setOnEndsCallback(std::function<void(void)> callback);
    void setOnLineEndsCallback(std::function<void(void)> callback);
    void setOnParagraphEndsCallback(std::function<void(void)> callback);
    
protected:
    void runSubstr(int start, int end);
    
};

class TypewriterLabel : public AnimationLabel{
public:
    TypewriterLabel();
    ~TypewriterLabel();
    static TypewriterLabel * createWithTTF(const std::string& text, const std::string& fontFile,
                                          float fontSize, float rubyfontSize = 0,
                                          const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
                                          TextVAlignment vAlignment = TextVAlignment::TOP);
private:
    double delayTime;
    
public:
    void setDelayTime(double delayTime);
    void runWithDelayTime(double delayTime);
    
};

class FadeinLabel : public AnimationLabel{
public:
    FadeinLabel();
    ~FadeinLabel();
    static FadeinLabel * createWithTTF(const std::string& text, const std::string& fontFile,
                                           float fontSize, float rubyfontSize = 0,
                                           const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
                                           TextVAlignment vAlignment = TextVAlignment::TOP);
private:
    double delayTime;
    double fadeinTime;

public:
    void setDelayTime(double delayTime);
    void setFadeinTime(double fadeinTime);
    void runWithDelayFadeinTime(double delayTime, double fadeinTime);
    
};

#endif /* defined(__Novelio__LetterAnimationLabel__) */
