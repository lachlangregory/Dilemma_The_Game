<template lang="html">
  <section>
    <div class="hero is-primary has-text-centered">
      <div class="hero-body">
        <div class="title">
          <h1 class="title is-2">Dilemma</h1>
        </div>
      </div>
    </div>
    <div style="padding-top: 40px;" class="container">
      <div class="columns">
        <div class="column"></div>
        <div class="column">
          <div class="has-text-right">
          <input class="button is-info is-small has-text-weight-bold" type="button" value="Reset Game" onClick="document.location.reload(true)">
        </div>
          <table class="table is-striped is-hoverable">
            <thead>
              <tr>
                <th><abbr title="Position">No.</abbr></th>
                <th>Players</th>
                <th>1</th>
                <th>2</th>
                <th>3</th>
                <th>4</th>
                <th>5</th>
                <th>6</th>
                <th>7</th>
                <th>8</th>
                <th>Total Score</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="player in scores" :key="player.name">
                <th>{{ player.number }}</th>
                <td><strong>{{ player.name }}</strong></td>
                <td>{{ player.roundScore[0] }}</td>
                <td>{{ player.roundScore[1] }}</td>
                <td>{{ player.roundScore[2] }}</td>
                <td>{{ player.roundScore[3] }}</td>
                <td>{{ player.roundScore[4] }}</td>
                <td>{{ player.roundScore[5] }}</td>
                <td>{{ player.roundScore[6] }}</td>
                <td>{{ player.roundScore[7] }}</td>
                <td><strong>{{ player.total }}</strong></td>
              </tr>
            </tbody>
          </table>
          <div class="is-size-5 has-text-centered">
            <p><span class="has-text-weight-bold has-text-success">Positive Multiplier:</span> {{posMulti}}</p>
            <p><span class="has-text-weight-bold has-text-danger">Negative Multiplier:</span> {{negMulti}}</p>
          </div>
        </div>
        <div class="column"></div>
      </div>
    </div>
    <div class="container" style="padding-top: 40px;">
      <div class="columns is-centered has-text-centered">
        <div class="column is-narrow">
          <b-field>
              <b-input v-model="scores[0].name" placeholder="Player 1"
                  size="is-medium">
              </b-input>
          </b-field>
          <br/>
          <b-switch v-model="scores[0].decision"
                    true-value="Steal"
                    false-value="Safe"
                    size="is-medium"
                    type="is-danger">
                    {{ scores[0].decision }}
          </b-switch>
        </div>
        <div class="column is-narrow">
          <b-field>
              <b-input v-model="scores[1].name" placeholder="Player 2"
                  size="is-medium">
              </b-input>
          </b-field>
          <br/>
          <b-switch v-model="scores[1].decision"
                    true-value="Steal"
                    false-value="Safe"
                    size="is-medium"
                    type="is-danger">
                    {{ scores[1].decision }}
          </b-switch>
        </div>
        <div class="column is-narrow">
          <b-field>
              <b-input v-model="scores[2].name" placeholder="Player 3"
                  size="is-medium">
              </b-input>
          </b-field>
          <br/>
          <b-switch v-model="scores[2].decision"
                    true-value="Steal"
                    false-value="Safe"
                    size="is-medium"
                    type="is-danger">
                    {{ scores[2].decision }}
          </b-switch>
        </div>
      </div>
    </div>
    <div class="columns is-centered has-text-centered">
      <div class="column is-narrow" style="padding-top: 40px;">
        <button @click="submitAnswers" class="button is-primary is-medium has-text-weight-bold">LOCK IN DECISIONS</button>
      </div>
    </div>
  </section>
</template>

<script>
export default {
  data () {
    return {
      numberOfPlayers: 3,
      numberOfRounds: 8,
      scores: [],
      negMulti: 1,
      posMulti: 1,
      steal: 0,
      safe: 0
    }
  },
  created: function () {
    let players = this.numberOfPlayers + 1
    for (let i = 1; i < players; i++) {
      let obj = {
        number: i,
        name: 'Player ' + i,
        decision: 'Safe',
        roundScore: [],
        total: 0
      }
      this.scores.push(obj)
    }
  },
  methods: {
    totalPoints: function () {
      let players = this.numberOfPlayers
      for (let i = 0; i < players; i++) {
        var sum = 0
        if (this.scores[i].roundScore.length) {
          for (var j in this.scores[i].roundScore) {
            sum += this.scores[i].roundScore[j]
          }
          this.scores[i].total = sum
        }
      }
    },
    checkMulti: function () {
      if (this.posMulti <= 0) {
        this.posMulti = 0.1
      }
      if (this.negMulti <= 0) {
        this.negMulti = 0.1
      }
    },
    checkResult: function () {
      // tally is the number of 'steals'
      let tally = 0
      for (var player in this.scores) {
        if (this.scores[player].decision == 'Steal') {
          tally ++
        }
      }
      if (tally == 3) {
        this.steal = -3 * this.negMulti
        this.posMulti -= 0.25
        this.negMulti += 1
      } else if (tally == 2) {
        this.steal = 1 * this.posMulti
        this.posMulti -= 0.25
        this.negMulti += 0.25
      } else if (tally == 1) {
        this.steal = 4 * this.posMulti
      } else {
        this.safe = 1 * this.posMulti
        this.posMulti += 0.5
        this.negMulti -= 0.25
      }
      this.checkMulti()
    },
    giveScore: function () {
      for (var player in this.scores) {
        if (this.scores[player].decision == 'Safe') {
          this.scores[player].roundScore.push(this.safe)
        } else {
          this.scores[player].roundScore.push(this.steal)
        }
      }
    },
    submitAnswers: function () {
      this.checkResult()
      this.giveScore()
      this.totalPoints ()
      for (var player in this.scores) {
        this.scores[player].decision = 'Safe'
      }
      this.steal = 0
      this.safe = 0
      if (this.scores[0].roundScore.length == this.numberOfRounds) {
        this.endGame()
      }
    },
    endGame() {
      this.$dialog.alert({
          title: 'Game Over',
          message: `The final scores are: <br/> <br/>
          ${this.scores[0].name} : <strong>${this.scores[0].total}</strong><br/>
          ${this.scores[1].name} : <strong>${this.scores[1].total}</strong><br/>
          ${this.scores[2].name} : <strong>${this.scores[2].total}</strong><br/>`,
          // message: 'The final scores are:<br>' + this.scores[0].name + ' : <strong>' + this.scores[0].total + '</stong><br>' this.scores[1].name + ' : <strong>' + this.scores[1].total + '</stong><br>' this.scores[2].name + ' : <strong>' + this.scores[2].total + '</stong><br>',
          confirmText: 'Play Again!',
          onConfirm: () => document.location.reload(true)
      })
    },
  }
}
</script>

<style lang="css">
</style>
