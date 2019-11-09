#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

GLfloat ballX = 0.0f;
GLfloat ballY = 0.0f;

class Player{
    private:
        float paddlelength = 0.4;
        float paddlewidth = 0.01;
        char playerName;
        float controller = 0.0f;
        int score = 0;
    public:
        Player(char a){
            playerName = a;
        }
        void DrawPaddle(){
            glPushMatrix();
            if(playerName=='a'){
                glBegin(GL_QUADS);
                glColor3f(1,0.0,0.0);
                glVertex2f(xMaxNegative +0.05 +0.01 + paddlewidth,controller + paddlelength/2);
                glVertex2f(xMaxNegative +0.05 +0.01,controller + paddlelength/2);
                glVertex2f(xMaxNegative +0.05 +0.01,controller - paddlelength/2);
                glVertex2f(xMaxNegative +0.05 +0.01 + paddlewidth,controller - paddlelength/2);
                glEnd();
            }
            else if(playerName=='b'){
                glBegin(GL_QUADS);
                glColor3f(0,0.0,1.0);
                glVertex2f(xMaxPositive -0.05 -0.01 - paddlewidth,controller + paddlelength/2);
                glVertex2f(xMaxPositive -0.05 -0.01,controller + paddlelength/2);
                glVertex2f(xMaxPositive -0.05 -0.01,controller - paddlelength/2);
                glVertex2f(xMaxPositive -0.05 -0.01 - paddlewidth,controller - paddlelength/2);
                glEnd();
            }
            glPopMatrix();
        }
        void MovePaddleUp(){
            if(controller + paddlelength/2 + 0.01 + 0.05 > yMaxPositive){
                controller = yMaxPositive - 0.05 - 0.01 - paddlelength/2;
            }
            else{
                controller +=0.0000005;
            }
        }
        void MovePaddleDown(){
            if( controller - paddlelength/2 - 0.01 - 0.05 < yMaxNegative){
                controller = yMaxNegative + 0.05 + 0.01 + paddlelength/2;
            }
            else{
                controller -=0.0000005;
            }
        }
        bool hitingpaddle(float bally){
            if((bally+0.05>controller-paddlelength/2) && (bally-0.05<controller+paddlelength/2)){
                return true;
            }
            else {
                return false;
            }
        }
        void scoreUpdate(){
            score++;
        }
        int showScore(){
            return score;
        }
        bool Scorereached(){
            if((score==7&&GameMode1==true)||(score==3&&GameMode2==true)||(score==10&&GameMode3==true)){
                return true;
            }
            else{
                return false;
            }
        }
        void scoreZero(){
            score =0;
        }
        void CPULogics(){
            if(controller < ballY){
                controller+=0.02;
            }
            else if(controller > ballY){
                controller-=0.02;
            }
        }
        void alterpaddlelength(float a){
                paddlelength = a;
        }
}Player1('a'),Player2('b');

class BallClass{
    private:
        GLfloat ballRadius = 0.03f;
        GLfloat ballXMax, ballXMin, ballYMax, ballYMin;
        GLfloat xSpeed = 0.01f;
        GLfloat ySpeed = 0.003f;
    public:
        BallClass(){
            xSpeed = pow((-1),random(10))*(random(10)/1000 + 0.03);
            ySpeed = pow((-1),random(10))*(random(10)/1000 + 0.03);
        }
        void resetBall(){
            Sleep(1000);
            ballRadius = 0.03f;
            xSpeed = pow((-1),random(10))*(random(10)/1000 + 0.03);
            ySpeed = pow((-1),random(10))*(random(10)/1000 + 0.03);
            ballX =0.0f;
            ballY =0.0f;
        }
        float YposOfBall(){return ballY;}
        void PlantBall(){
            ballXMin = xMaxNegative + ballRadius + 0.05 + 0.01 +0.02;
            ballXMax = xMaxPositive - ballRadius - 0.05 - 0.01 -0.02;
            ballYMin = yMaxNegative + ballRadius + 0.05 +0.03;
            ballYMax = yMaxPositive - ballRadius - 0.05 -0.03;
            glPushMatrix();
            glTranslatef(ballX, ballY, 0.0f);
            glBegin(GL_TRIANGLE_FAN);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(0.0f, 0.0f);
            int numSegments = 100;
            GLfloat angle;
            for (int i = 0; i <= numSegments; i++) {
                angle = i * 2.0f * PI / numSegments;
                glVertex2f(cos(angle) * ballRadius, sin(angle) * ballRadius);
            }
            glEnd();
            glPopMatrix();
        }
        void ApplyBallLogicsForMotion(){
            if(Player1.Scorereached()==false || Player2.Scorereached()==false)
            if((ballX > ballXMax)){
                if((Player2.hitingpaddle(ballY)==true))
                {
                    ballX = ballXMax;
                    xSpeed = -xSpeed+(-xSpeed/20);
                }
                else{
                    Player1.scoreUpdate();
                    resetBall();
                }
            } else if((ballX < ballXMin)){
                if((Player1.hitingpaddle(ballY)==true))
                {
                    ballX = ballXMin;
                    xSpeed = -xSpeed+(-xSpeed/20);
                }
                else{
                    Player2.scoreUpdate();
                    resetBall();
                }
            }
            else {
                ballX += xSpeed;
            }

            if(Player1.Scorereached()==false || Player2.Scorereached()==false)
            if(ballY > ballYMax){
                ballY = ballYMax;
                ySpeed = -ySpeed;
            } else if(ballY < ballYMin){
                ballY = ballYMin;
                ySpeed = -ySpeed;
            }
            else {
                ballY += ySpeed;
            }

            if(Player1.Scorereached()==true || Player2.Scorereached()==true){
                if(GameMode1==true)
                {
                    GameMode1Result = true;
                    GameMode1 = false;
                }
                if(GameMode2==true){
                    GameMode2Result = true;
                    GameMode2 = false;
                }
                if(GameMode3==true)
                {
                    GameMode3Result = true;
                    GameMode3 = false;
                }
            }
        }
        void proLogics(){
            if(Player1.showScore()==1||Player1.showScore()==1){
                ballRadius=0.02;
            }
            if(Player1.showScore()==2){
                Player1.alterpaddlelength(0.2);
            }
            if(Player2.showScore()==2){
                Player2.alterpaddlelength(0.2);
            }
        }
}Ball;

#endif
