import DroneControlControl as dc
import DQNAgent
import numpy as np
import time

def step(action):
    res = dc.step_state(action).getZ()
    next_state = np.array([res])
    reward = -abs(res)
    done = False
    return next_state, reward, done

def trainDrone():

    episodes = 100

    state_size = 1
    action_size = 1
    agent = DQNAgent.DQNAgent(state_size, action_size)

        # Iterate the game
    for e in range(episodes):
        # reset state in the beginning of each game
        state = np.array([dc.reset().getZ()])
        # time_t represents each frame of the game
        # Our goal is to keep the pole upright as long as possible until score of 500
        # the more time_t the more score
        tot_reward = 0

        for time_t in range(500):
            # Decide action
            action = agent.act(state, e)
            print(action)
            # Advance the game to the next frame based on the action.
            # Reward is 1 for every frame the pole survived
            next_state, reward, done = step(action)

            tot_reward += reward
            # Remember the previous state, action, reward, and done
            agent.remember(state, action, reward, next_state, done)
            # make next_state the new current state for the next frame.
            state = next_state
            # done becomes True when the game ends
            # ex) The agent drops the pole
            if done:
                break
        # train the agent with the experience of the episode

        # print the score and break out of the loop
        print("episode: {}/{}, score: {}"
            .format(e, episodes, tot_reward))
        t = time.time()
        agent.replay(64)
        elapsed = time.time() - t
        print(elapsed)

def main():
    dc.start()
    trainDrone()
    dc.kill()

if __name__ == '__main__':
    main()