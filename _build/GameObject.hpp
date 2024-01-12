#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>


namespace IB
{
	class GameObject
	{
		Vector3 position;
		//Vector3* mesh; todo: use this later
		bool isLight;


		GameObject()
		{
			position = Vector3(0.0f, 0.0f, 0.0f);
			isLight = false;
			//mesh = new Vector3[];
		}


		~GameObject()
		{
			//delete mesh;
		}
	};

    class SimulationObject {
    private:
        float mass;
        Vector3 position; // Assuming position is a Vector3
        Vector3 velocity; // Assuming velocity is a Vector3
        bool BigMass; //1 unit bigmass = 10^20 kg

    public:
        // Setter for mass
        void setMass(float newMass, bool isBigMass) {
            mass = newMass;
            BigMass = isBigMass;
        }

        // Setter for position
        void setPosition(const Vector3& newPosition) {
            position = newPosition;
        }

        // Setter for velocity
        void setVelocity(const Vector3& newVelocity) {
            velocity = newVelocity;
        }

        // Default constructor
        SimulationObject() : mass(1.0), position(Vector3()), velocity(Vector3()), BigMass(false) {}

        // Constructor with parameters
        SimulationObject(float initialMass, bool initialBigMass, const Vector3& initialPosition, const Vector3& initialVelocity)
            : mass(initialMass), position(initialPosition), velocity(initialVelocity), BigMass(initialBigMass) {}

        // Getter for mass
        float getMass() const {
            return mass;
        }

        // Getter for position
        const Vector3& getPosition() const {
            return position;
        }

        // Getter for velocity
        const Vector3& getVelocity() const {
            return velocity;
        }

        // Function to update velocity based on force, deltaMass, and deltaTime
        void applyForceWithMassChangeSmallMass(const Vector3& force, float deltaMass, float deltaTime) {
            Vector3 acceleration;
            acceleration = force / (mass + deltaMass);

            velocity = velocity + acceleration * deltaTime;

            position = position + velocity * deltaTime;
        }

        void applyForceSmallMass(const Vector3& force, float deltaTime) {
            Vector3 acceleration;
            acceleration = force / mass;

            velocity = velocity + acceleration * deltaTime;

            position = position + velocity * deltaTime;
        }

        //exact same as small mass function, only exists for understanding how much force and what mass it is
        void applyForceBigMass(const Vector3& force, float deltaTime) {
            Vector3 acceleration;
            acceleration = force / mass;

            velocity = velocity + acceleration * deltaTime;

            position = position + velocity * deltaTime;
        }
    };

    class MyCamera
    {
        Vector3 position;
        Vector3 ForwardDirection;
        float focal_length;
    };
}