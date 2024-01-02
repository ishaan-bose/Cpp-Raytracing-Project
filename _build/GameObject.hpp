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
        double mass;
        Vector3 position; // Assuming position is a Vector3
        Vector3 velocity; // Assuming velocity is a Vector3

    public:
        // Default constructor
        SimulationObject() : mass(1.0), position(Vector3()), velocity(Vector3()) {}

        // Constructor with parameters
        SimulationObject(double initialMass, const Vector3& initialPosition, const Vector3& initialVelocity)
            : mass(initialMass), position(initialPosition), velocity(initialVelocity) {}

        // Getter for mass
        double getMass() const {
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
        void applyForce(const Vector3& force, double deltaMass, double deltaTime) {
            Vector3 acceleration;
            acceleration.x = force.x / (mass + deltaMass);
            acceleration.y = force.y / (mass + deltaMass);
            acceleration.z = force.z / (mass + deltaMass);

            velocity.x += acceleration.x * deltaTime;
            velocity.y += acceleration.y * deltaTime;
            velocity.z += acceleration.z * deltaTime;
        }
    };
}