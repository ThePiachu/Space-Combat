#include "steering.h"

/*
	myvector steering::arrive(const point& Position, const myvector& Velocity, const point& Target,
			const float& SlowingDistance)//,//distance where the slowing gets triggered
			const
	{
		myvector result(Position, Target);
		result/=SlowingDistance;
		if (result.getsquaredmagnitude()>1.0)
		{
			result.normaliseme();
		}
		return result-=Velocity;
	}
	inline
	myvector steering::seek(const point& Position, const myvector& Velocity,
			const point& Target, const float& TargetRadius)
			const
	{
		myvector result(Position, Target);
		result.setmymagnitude(result.getmagnitude()-TargetRadius);
		if (result.getsquaredmagnitude()>1.0)result.normaliseme();
		return result-=Velocity;
	}
	inline
	myvector steering::flee(const point& Position, const myvector& Velocity, const point& Target)
			const
	{
		return -seek(Position, Velocity, Target);
	}
	inline
	myvector steering::wander(
			const myvector& Velocity,//way it is facing
			const float& WanderDomeSpread)//how wide is the angle of the dome
			const
	{
		if(Velocity.getsquaredmagnitude()==0.0)return myvector(0.0, 1.0, 0.0);
		return this->myrandom->randomdomeposition(Velocity, WanderDomeSpread).normaliseme()-Velocity;
	}
	inline
	myvector steering::followline(const point& Position,//position of the agent
			const myvector& Velocity,//way it is facing
			const line& Line,//the line to follow
			const float& MaxDistance)//maximum distance allowed from line
			const
	{
		myvector anwser(0.0, 0.0, 0.0);
		if (Line.distanceto(Position)<MaxDistance)//if position is close enough to line, no steering
			return anwser;
		else
		{//otherwise steering towwards the line
			anwser(Position, Line.projection(Position))/=MaxDistance;//anwser is proportional to distance form the line and max distance
			anwser.setmymagnitude(anwser.getmagnitude()-1.0);//at distance=MaxDistance, it is 0, and is continuous at higher distances
			anwser.setmymagnitude(anwser.getsquaredmagnitude());//function is quadratic
			if (anwser.getsquaredmagnitude()>1.0) anwser.normaliseme();
			return anwser-=Velocity;
		}
	}
	myvector steering::followpathsegment(const point& Position,//position of the agent
			const myvector& Velocity,//way it is facing
			const pathsegment& Path,//the line to follow
			const float& MaxDistance,//maximum distance allowed from line
			const float MoveForwardRatio)//how more important moving forward is to following the line
			const
	{
		myvector tmpvector, tmpvector2;
		if (Path.myline.distanceto(Position)<MaxDistance)//if position is close enough to line, no steering
			tmpvector(0.0, 0.0, 0.0);
		else
		{//line following
			tmpvector(Position, Path.myline.projection(Position))/=MaxDistance;
			tmpvector.setmymagnitude(tmpvector.getmagnitude()-1.0);//at distance=MaxDistance, it is 0, and is continuous at higher distances
			tmpvector.setmymagnitude(tmpvector.getsquaredmagnitude());//function is quadratic
		}
		//plane following
		tmpvector2(Position, Path.myplane.projection(Position));
		if (tmpvector2.getsquaredmagnitude()<1.0) tmpvector2.normaliseme();
		//if (tmpvector2.getsquaredmagnitude()>1.0) tmpvector2.normaliseme();
		//tmpvector2-=Velocity;
		//adding them together
		if ((tmpvector+=tmpvector2*=MoveForwardRatio).getsquaredmagnitude()>1.0)tmpvector.normaliseme();
		return tmpvector;//-=Velocity;
	}
	myvector steering::separation
		(
			const point& Position,//position of the agent
			const myvector& Velocity,
			const point& AveragePosition//,
			//const float& FunctionCoefficient
		) const
	{
		myvector tmp=myvector(AveragePosition, Position);
		float mag=tmp.getmagnitude();
		if (mag==0) return myvector(0.0, 0.0, 0.0);
		else tmp.setmymagnitude(1.0/mag);
		if (tmp.getsquaredmagnitude()>1.0)tmp.normaliseme();
		return tmp;
	}
	inline
	myvector steering::alignment
		(
			const myvector& Velocity,
			const myvector& AverageVelocity
		) const
	{
		myvector tmpvector=AverageVelocity-Velocity;
		if (tmpvector.getsquaredmagnitude()>1.0)tmpvector.normaliseme();
		return tmpvector;
	}
	inline
	myvector steering::cohersion
		(
			const point& Position,//position of the agent
			const myvector& Velocity,//speed of the agent
			const point& AveragePosition
		) const
	{
		return seek(Position, Velocity, AveragePosition);
	}
	inline
	myvector steering::stop(const myvector& Forward) const
	{
		if (Forward.getsquaredmagnitude()>1.0)return (-Forward).normaliseme();
		else return -Forward;
	}
	myvector steering::avoidcolision(const point& Position, const float& Radius,
			const point& Target, const float& TargetRadius,
			const float& TriggerDistance
			) const
	{
		float distance=abs(Position.distanceto(Target)-Radius-TargetRadius);
		if (distance>TriggerDistance) return myvector();
		if (Position==Target) return myvector();
		else return myvector(Position, Target).setmymagnitude(1-TriggerDistance/distance);
	}
	inline
	myvector steering::gravitate
		(
			const point& Position,
			const myvector& Velocity,
			const point& Target,
			const float& Distance
		) const
	{
		myvector anwser(Position, Target);
		anwser.setmymagnitude(anwser.getmagnitude()/Distance*anwser.getmagnitude()/Distance);
		if (anwser.getsquaredmagnitude()>1.0)anwser.normaliseme();
		return anwser-=Velocity;
	}
	inline
	myvector steering::gravitatesqrt
		(
			const point& Position,
			const myvector& Velocity,
			const point& Target,
			const float& Distance
		) const
	{
		myvector anwser(Position, Target);
		anwser.setmymagnitude(sqrt(anwser.getmagnitude()/Distance));
		if (anwser.getsquaredmagnitude()>1.0)anwser.normaliseme();
		return anwser-=Velocity;
	}*/

